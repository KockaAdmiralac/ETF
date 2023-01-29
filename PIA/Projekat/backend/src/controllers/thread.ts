import {Request, Response, Router} from 'express';
import {
    ThreadInfo,
    extractMessageInfo,
    extractThreadInfo
} from '../util/transform';
import {
    getCurrentUser,
    getUserProps,
    isLoggedInMiddleware,
    isOrganization
} from '../util/auth';
import {Database} from '../util/database';
import Message from '../entities/Message';
import Thread from '../entities/Thread';
import User from '../entities/User';
import {primitives} from '@altostra/type-validations';
import {validateRequest} from '../util/validation';

const router = Router();

/**
 * Validates that the ID specified in the API call is a valid thread ID and
 * returns the thread if so. If the ID has not been specified, or the thread
 * does not exist, it responds to the request with the correct error message and
 * returns null.
 * @param req Express request data
 * @param res Express response to reply to
 * @returns Found thread, or null if no thread was found
 */
async function validateThreadExists(
    req: Request,
    res: Response
): Promise<Thread | null> {
    if (typeof req.params['id'] !== 'string') {
        res.status(400).json({
            id: 'Invalid request body.'
        });
        return null;
    }
    const id = Number(req.params['id']);
    const thread = await Database.getRepository(Thread).findOne({
        relations: {
            messages: {
                user: true
            },
            user: true,
            workshop: true
        },
        where: {id}
    });
    if (!thread) {
        res.status(400).json({
            id: 'Specified thread does not exist.'
        });
        return null;
    }
    return thread;
}

router.get('/', isLoggedInMiddleware, async function(req, res) {
    const user = await getCurrentUser(req);
    const threads: ThreadInfo[] = [];
    if (user && isOrganization(req)) {
        threads.push(...(await Database.getRepository(Thread).find({
            relations: {
                messages: true
            },
            where: {
                workshop: {
                    user: {
                        id: user.id
                    }
                }
            }
        })).map(extractThreadInfo));
    } else if (user) {
        const userWithThreads = await Database
            .getRepository(User)
            .createQueryBuilder('user')
            .leftJoinAndSelect('user.threads', 'threads')
            .where('user.id = :userId', {
                userId: user.id
            })
            .getOne();
        const userThreads = userWithThreads!.threads!;
        for (const thread of userThreads) {
            thread.messages = [];
        }
        threads.push(...userThreads.map(extractThreadInfo));
    }
    res.json({threads});
});

router.get('/:id/messages', isLoggedInMiddleware, async function(req, res) {
    const thread = await validateThreadExists(req, res);
    if (!thread) {
        return;
    }
    const userId = getUserProps(req).id;
    if (thread.user.id !== userId && thread.workshop.user.id !== userId) {
        res.status(400).json({
            error: 'Your cannot view conversations of other users.'
        });
        return;
    }
    const messages = thread.messages.map(extractMessageInfo);
    res.json({messages});
});

router.post('/:id/messages', isLoggedInMiddleware, async function(req, res) {
    const thread = await validateThreadExists(req, res);
    if (!thread || !validateRequest({
        text: primitives.string
    }, req.body, res)) {
        return;
    }
    const user = await getCurrentUser(req);
    if (
        !user ||
        thread.user.id !== user.id &&
        thread.workshop.user.id !== user.id
    ) {
        res.status(400).json({
            error: 'Your cannot view conversations of other users.'
        });
        return;
    }
    const message = new Message();
    message.text = req.body.text;
    message.thread = thread;
    message.user = user;
    await Database.getRepository(Message).save(message);
    res.json({message});
});

export default router;
