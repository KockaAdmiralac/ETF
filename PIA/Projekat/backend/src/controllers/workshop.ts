import {LessThan, MoreThan, Not} from 'typeorm';
import {Request, Response, Router} from 'express';
import Signup, {SignupStatus} from '../entities/Signup';
import User, {UserRole} from '../entities/User';
import {arrayOf, maybe, primitives} from '@altostra/type-validations';
import {copyFile, writeFile} from 'fs/promises';
import {
    extractCommentInfo,
    extractThreadInfo,
    extractUserInfo,
    extractWorkshopInfo
} from '../util/transform';
import {
    getCurrentUser,
    getUserProps,
    isAdmin,
    isAdminMiddleware,
    isLoggedInMiddleware,
    isOrganizationMiddleware,
    jwt
} from '../util/auth';
import Comment from '../entities/Comment';
import {Database} from '../util/database';
import Photo from '../entities/Photo';
import Thread from '../entities/Thread';
import Workshop from '../entities/Workshop';
import config from '../../config.json';
import multer from 'multer';
import {sendEmail} from '../util/email';
import {validateRequest} from '../util/validation';

const router = Router();
const upload = multer({
    storage: multer.memoryStorage()
});

/**
 * Validates that the ID specified in the API call is a valid workshop ID and
 * returns the workshop if so. If the ID has not been specified, or the workshop
 * does not exist, it responds to the request with the correct error message and
 * returns null.
 * @param req Express request data
 * @param res Express response to reply to
 * @returns Found workshop, or null if no workshop was found
 */
async function validateWorkshopExists(
    req: Request,
    res: Response
): Promise<Workshop | null> {
    if (typeof req.params['id'] !== 'string') {
        res.status(400).json({
            id: 'Invalid request body.'
        });
        return null;
    }
    const id = Number(req.params['id']);
    const workshop = await Database.getRepository(Workshop).findOneBy({id});
    if (!workshop) {
        res.status(400).json({
            id: 'Specified workshop does not exist.'
        });
        return null;
    }
    return workshop;
}

router.get('/', jwt, async function(req, res) {
    const workshops = (await Database.getRepository(Workshop).find())
        .map(extractWorkshopInfo);
    const userProps = 'auth' in req && getUserProps(req);
    const signups = userProps ? (await Database.getRepository(Signup).find({
        relations: {
            workshop: true
        },
        where: {
            status: SignupStatus.PARTICIPATING,
            user: {
                id: userProps.id
            }
        }
    })).map(signup => signup.workshop.id) : [];
    res.json({
        signups,
        workshops
    });
});

router.post('/', isLoggedInMiddleware, async function(req, res) {
    if (!validateRequest({
        capacity: primitives.number,
        date: primitives.string,
        description: primitives.string,
        latitude: primitives.number,
        longitude: primitives.number,
        name: primitives.string,
        place: primitives.string,
        snippet: primitives.string
    }, req.body, res)) {
        return;
    }
    const workshop = new Workshop();
    Object.assign(workshop, req.body);
    workshop.active = isAdmin(req);
    workshop.comments = [];
    workshop.likedUsers = [];
    workshop.photos = [];
    const user = await getCurrentUser(req);
    if (user) {
        workshop.user = user;
    }
    await Database.getRepository(Workshop).save(workshop);
    res.json({
        workshop: extractWorkshopInfo(workshop)
    });
});

router.put('/:id/likes', isLoggedInMiddleware, async function(req, res) {
    const workshop = await validateWorkshopExists(req, res);
    if (!workshop) {
        return;
    }
    const user = await getCurrentUser(req);
    if (user && !workshop.likedUsers.some(u => u.id === user.id)) {
        workshop.likedUsers.push(user);
        await Database.getRepository(Workshop).save(workshop);
    }
    res.json({success: true});
});

router.delete('/:id/likes', isLoggedInMiddleware, async function(req, res) {
    const workshop = await validateWorkshopExists(req, res);
    if (!workshop) {
        return;
    }
    const user = await getCurrentUser(req);
    if (user) {
        workshop.likedUsers = workshop.likedUsers.filter(u => u.id !== user.id);
        await Database.getRepository(Workshop).save(workshop);
    }
    res.json({success: true});
});

router.put('/:id/comments', isLoggedInMiddleware, async function(req, res) {
    const workshop = await validateWorkshopExists(req, res);
    if (!workshop || !validateRequest({
        text: primitives.string
    }, req.body, res)) {
        return;
    }
    const user = await getCurrentUser(req);
    const comment = new Comment();
    if (user) {
        comment.text = req.body.text;
        comment.user = user;
        comment.workshop = workshop;
        await Database.getRepository(Comment).save(comment);
    }
    res.json({
        comment,
        success: true
    });
});

router.patch(
    '/:id/comments/:commentId',
    isLoggedInMiddleware,
    async function(req, res) {
        const workshop = await validateWorkshopExists(req, res);
        if (
            !workshop ||
            !validateRequest({
                commentId: primitives.string
            }, req.params, res) ||
            !validateRequest({
                text: primitives.string
            }, req.body, res)
        ) {
            return;
        }
        const id = Number(req.params.commentId);
        const commentRepo = Database.getRepository(Comment);
        const comment = await commentRepo.findOneBy({id});
        if (!comment) {
            res.status(400).json({
                id: 'Specified comment does not exist.'
            });
            return;
        }
        const user = await getCurrentUser(req);
        if (
            !user ||
            comment.user.id !== user.id &&
            user.role !== UserRole.ADMIN
        ) {
            res.status(403).json({
                id: 'You cannot update comments of other users.'
            });
            return;
        }
        comment.text = req.body.text;
        await commentRepo.save(comment);
        res.json({success: true});
    }
);

router.delete(
    '/:id/comments/:commentId',
    isLoggedInMiddleware,
    async function(req, res) {
        const workshop = await validateWorkshopExists(req, res);
        if (!workshop) {
            return;
        }
        const id = Number(req.params['commentId']);
        const commentRepo = Database.getRepository(Comment);
        const comment = await commentRepo.findOneBy({id});
        if (!comment) {
            res.status(400).json({
                id: 'Specified comment does not exist.'
            });
            return;
        }
        const user = await getCurrentUser(req);
        if (
            !user ||
            comment.user.id !== user.id &&
            user.role !== UserRole.ADMIN
        ) {
            res.status(403).json({
                id: 'You cannot delete comments of other users.'
            });
            return;
        }
        await commentRepo.delete({id});
        res.json({success: true});
    }
);

router.put('/:id/users', isLoggedInMiddleware, async function(req, res) {
    const workshop = await validateWorkshopExists(req, res);
    if (!workshop) {
        return;
    }
    const user = await getCurrentUser(req);
    const signupRepo = Database.getRepository(Signup);
    const existentSignup = await signupRepo.findOneBy({
        user: {
            id: user?.id
        },
        workshop: {
            id: workshop.id
        }
    });
    const signup = existentSignup ?? new Signup();
    const alreadyRequested = existentSignup &&
                             existentSignup.status !== SignupStatus.QUEUED;
    signup.workshop = workshop;
    if (user) {
        signup.user = user;
    }
    const reserved = await signupRepo.count({
        where: {
            status: Not(SignupStatus.QUEUED),
            workshop: {
                id: workshop.id
            }
        }
    }) - Number(alreadyRequested);
    if (workshop.capacity <= reserved) {
        signup.status = SignupStatus.QUEUED;
    } else {
        signup.status = SignupStatus.REQUESTED;
    }
    await Database.getRepository(Signup).save(signup);
    res.json({
        status: signup.status,
        success: true
    });
});

router.delete('/:id/users', isLoggedInMiddleware, async function(req, res) {
    const workshop = await validateWorkshopExists(req, res);
    if (!workshop) {
        return;
    }
    const reserved = await Database.getRepository(Signup).count({
        where: {
            status: Not(SignupStatus.QUEUED),
            workshop: {
                id: workshop.id
            }
        }
    });
    const user = await getCurrentUser(req);
    if (user) {
        try {
            await Database.getRepository(Signup).delete({
                user: {
                    id: user.id
                },
                workshop: {
                    id: workshop.id
                }
            });
        } catch (error) {
            res.status(400).json({
                error: 'Not signed up for this workshop.'
            });
            return;
        }
    }
    res.json({success: true});
    if (workshop.capacity === reserved) {
        // Email queued users since there is 1 free space right now.
        const workshopUrl = `${config.frontendUrl}/workshops/${workshop.id}`;
        const queuedSignups = await Database
            .getRepository(Signup)
            .createQueryBuilder('signup')
            .leftJoinAndSelect('signup.workshop', 'workshop')
            .leftJoinAndSelect('signup.user', 'user')
            .where('workshop.id = :workshopId', {
                workshopId: workshop.id
            })
            .where('signup.status = :queued', {
                queued: SignupStatus.QUEUED
            })
            .getMany();
        for (const signup of queuedSignups) {
            await sendEmail('free-place', {
                name: workshop.name,
                url: workshopUrl
            }, signup.user.email, 'Free place on a workshop');
        }
    }
});

router.get('/:id', isLoggedInMiddleware, async function(req, res) {
    const workshop = await validateWorkshopExists(req, res);
    if (!workshop) {
        return;
    }
    const signupRepo = Database.getRepository(Signup);
    const user = await getCurrentUser(req);
    const reserved = await signupRepo.count({
        where: {
            status: Not(SignupStatus.QUEUED),
            workshop: {
                id: workshop.id
            }
        }
    });
    const signup = user && await signupRepo.findOneBy({
        user: {
            id: user.id
        },
        workshop: {
            id: workshop.id
        }
    });
    const signups = await signupRepo.find({
        relations: {
            user: true
        },
        where: {
            status: SignupStatus.REQUESTED,
            workshop: {
                id: workshop.id
            }
        }
    });
    const isOwner = workshop.user.id === user?.id;
    const isFull = reserved === workshop.capacity;
    const signupStatus = signup ?
        signup.status === SignupStatus.PARTICIPATING ?
            'can-cancel' :
            signup.status === SignupStatus.REQUESTED ?
                'can-cancel' :
                isFull ?
                    'can-cancel' :
                    'can-sign-up' :
        isFull ?
            'can-queue' :
            'can-sign-up';
    const participatedBefore = user && await signupRepo.exist({
        where: {
            user: {
                id: user.id
            },
            workshop: {
                date: LessThan(new Date()),
                name: workshop.name
            }
        }
    });
    const liked = user && Boolean(
        workshop.likedUsers
            .find(u => u.id === user.id)
    );
    const comments = workshop.comments.map(c => extractCommentInfo(c));
    res.json({
        comments,
        liked,
        participatedBefore,
        signupStatus,
        signups: isOwner ? signups.map(s => extractUserInfo(s.user)) : [],
        workshop: extractWorkshopInfo(workshop)
    });
});

router.post('/:id/new-thread', isLoggedInMiddleware, async function(req, res) {
    const workshop = await validateWorkshopExists(req, res);
    if (!workshop) {
        return;
    }
    const threadRepo = Database.getRepository(Thread);
    const user = await getCurrentUser(req);
    const existentThread = await threadRepo
        .createQueryBuilder('thread')
        .leftJoinAndSelect('thread.workshop', 'workshop')
        .leftJoinAndSelect('thread.user', 'user')
        .where('workshop.id = :workshopId', {
            workshopId: workshop.id
        })
        .where('user.id = :userId', {
            userId: user?.id
        })
        .getOne();
    const thread = existentThread ?? new Thread();
    thread.workshop = workshop;
    if (user) {
        thread.user = user;
    }
    if (!existentThread) {
        await threadRepo.save(thread);
    }
    thread.messages = [];
    res.json({
        thread: extractThreadInfo(thread)
    });
});

router.post(
    '/:id/photos',
    isOrganizationMiddleware,
    upload.array('photos', 5),
    async function(req, res) {
        const workshop = await validateWorkshopExists(req, res);
        if (!workshop) {
            return;
        }
        const user = await getCurrentUser(req);
        if (user?.id !== workshop.user.id && !isAdmin(req)) {
            res.status(400).json({
                error: 'You cannot edit others\' workshops'
            });
            return;
        }
        if (!Array.isArray(req.files)) {
            res.status(400).json({
                error: 'No photos uploaded.'
            });
            return;
        }
        if (workshop.photos.length + req.files.length > 5) {
            res.status(400).json({
                error: 'Cannot upload more than 5 photos.'
            });
            return;
        }
        for (const file of req.files) {
            const photo = new Photo();
            photo.workshop = workshop;
            await Database.getRepository(Photo).save(photo);
            workshop.photos.push(photo);
            await writeFile(`public/upload/${photo.id}.png`, file.buffer);
        }
        res.json({
            photos: workshop.photos.map(p => p.id)
        });
    }
);

router.patch('/:id', isLoggedInMiddleware, async function(req, res) {
    const workshop = await validateWorkshopExists(req, res);
    if (!workshop || !validateRequest({
        active: primitives.maybeBoolean,
        capacity: primitives.maybeNumber,
        date: primitives.maybeString,
        description: primitives.maybeString,
        latitude: primitives.maybeNumber,
        longitude: primitives.maybeNumber,
        name: primitives.maybeString,
        photos: maybe(arrayOf<number>(primitives.number)),
        place: primitives.maybeString,
        snippet: primitives.maybeString
    }, req.body, res)) {
        return;
    }
    const {
        active, capacity, date: dateString, description, latitude, longitude,
        name, place, snippet
    } = req.body;
    const workshopName = workshop.name;
    const user = await getCurrentUser(req);
    if (user?.id !== workshop.user.id && !isAdmin(req)) {
        res.status(400).json({
            error: 'You cannot edit others\' workshops'
        });
        return;
    }
    const date = dateString && new Date(dateString);
    if (date && isNaN(date.getTime())) {
        res.status(400).json({
            error: 'Invalid date string.'
        });
        return;
    }
    Object.assign(workshop, {
        capacity,
        date,
        description,
        latitude,
        longitude,
        name,
        place,
        snippet
    });
    if (req.body.photos) {
        for (const id of req.body.photos) {
            const photoRepo = Database.getRepository(Photo);
            const photo = await photoRepo.findOneBy({id});
            if (photo) {
                const newPhoto = new Photo();
                newPhoto.workshop = workshop;
                await photoRepo.save(newPhoto);
                await copyFile(`public/upload/${id}.png`, `public/upload/${newPhoto.id}.png`);
                workshop.photos.push(newPhoto);
            }
        }
    }
    if (typeof active === 'boolean') {
        if (active && isAdmin(req)) {
            const hasActiveSignups = await Database
                .getRepository(Signup)
                .exist({
                    where: {
                        user: {
                            id: workshop.user.id
                        },
                        workshop: {
                            active: true,
                            date: MoreThan(new Date())
                        }
                    }
                });
            if (hasActiveSignups) {
                res.status(400).json({
                    error: 'User must not have active signups.'
                });
                return;
            }
            workshop.active = true;
            if (workshop.user.role !== UserRole.ADMIN) {
                workshop.user.role = UserRole.ORGANIZATION;
            }
            await Database.getRepository(User).save(workshop.user);
        } else if (!active) {
            workshop.active = false;
        }
        if (isAdmin(req) || !active) {
            workshop.active = active;
        }
        if (!workshop.active) {
            const workshopUrl = `${config.frontendUrl}/workshops/${workshop.id}`;
            const signups = await Database
                .getRepository(Signup)
                .createQueryBuilder('signup')
                .leftJoinAndSelect('signup.workshop', 'workshop')
                .leftJoinAndSelect('signup.user', 'user')
                .where('workshop.id = :workshopId', {
                    workshopId: workshop.id
                })
                .getMany();
            for (const signup of signups) {
                await sendEmail('cancellation', {
                    name: workshopName,
                    url: workshopUrl
                }, signup.user.email, 'Workshop cancelled');
            }
        }
    }
    await Database.getRepository(Workshop).save(workshop);
    res.json({success: true});
});

router.post(
    '/:id/signup/:userId',
    isOrganizationMiddleware,
    async function(req, res) {
        const workshop = await validateWorkshopExists(req, res);
        if (!workshop || !validateRequest({
            userId: primitives.string
        }, req.params, res)) {
            return;
        }
        const user = await getCurrentUser(req);
        if (user?.id !== workshop.user.id && !isAdmin(req)) {
            res.status(400).json({
                error: 'You cannot edit others\' workshops'
            });
            return;
        }
        await Database.getRepository(Signup).update({
            user: {
                id: Number(req.params.userId)
            }
        }, {
            status: SignupStatus.PARTICIPATING
        });
        res.json({sucess: true});
    }
);

router.delete('/:id', isAdminMiddleware, async function(req, res) {
    const workshop = await validateWorkshopExists(req, res);
    if (!workshop) {
        return;
    }
    await Database.getRepository(Workshop).delete({
        id: workshop.id
    });
    res.json({success: true});
});

export default router;
