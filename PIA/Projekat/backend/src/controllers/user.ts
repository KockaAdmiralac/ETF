import User, {UserRole, UserStatus} from '../entities/User';
import {enumOf, maybe, primitives} from '@altostra/type-validations';
import {
    extractCommentInfo,
    extractThreadInfo,
    extractUserInfo,
    extractWorkshopInfo
} from '../util/transform';
import {
    getUserProps,
    isAdminMiddleware,
    isLoggedInMiddleware
} from '../util/auth';
import {Database} from '../util/database';
import {Router} from 'express';
import Thread from '../entities/Thread';
import bcrypt from 'bcrypt';
import imageSize from 'image-size';
import multer from 'multer';
import {validateRequest} from '../util/validation';
import {writeFile} from 'fs/promises';

const router = Router();
const upload = multer({
    storage: multer.memoryStorage()
});

router.get('/', isAdminMiddleware, async function(_, res) {
    const users = (await Database.getRepository(User).find())
        .map(extractUserInfo);
    res.json({users});
});

router.get('/:id', isLoggedInMiddleware, async function(req, res) {
    if (!validateRequest({
        id: primitives.string
    }, req.params, res)) {
        return;
    }
    const userId = Number(req.params.id);
    const props = getUserProps(req);
    if (props.role !== UserRole.ADMIN && props.id !== userId) {
        res.status(403).json({
            error: 'You are not authorized to access this resource.'
        });
        return;
    }
    const user = await Database.getRepository(User).findOne({
        relations: {
            comments: {
                workshop: true
            },
            likedWorkshops: true
        },
        where: {
            id: userId
        }
    });
    const threads = await Database.getRepository(Thread).find({
        relations: {
            messages: {
                user: true
            },
            user: true,
            workshop: true
        },
        where: [
            {
                workshop: {
                    user: {
                        id: userId
                    }
                }
            },
            {
                user: {
                    id: userId
                }
            }
        ]
    });
    if (!user) {
        res.status(400).json({
            error: 'Specified user does not exist.'
        });
        return;
    }
    res.json({
        comments: user.comments?.map(c => extractCommentInfo(c, true)),
        email: user.email,
        likes: user.likedWorkshops.map(w => extractWorkshopInfo(w)),
        threads: threads.map(t => extractThreadInfo(t)),
        user: extractUserInfo(user)
    });
});

router.patch('/:id', isLoggedInMiddleware, async function(req, res) {
    if (
        !validateRequest({
            id: primitives.string
        }, req.params, res) ||
        !validateRequest({
            address: primitives.maybeString,
            email: primitives.maybeString,
            hasAvatar: primitives.maybeBoolean,
            name: primitives.maybeString,
            oid: primitives.maybeNumber,
            organization: primitives.maybeString,
            password: primitives.maybeString,
            phone: primitives.maybeString,
            role: maybe(enumOf<UserRole>(
                UserRole.ADMIN,
                UserRole.BASIC,
                UserRole.ORGANIZATION
            )),
            status: maybe(enumOf<UserStatus>(
                UserStatus.ACTIVE,
                UserStatus.INACTIVE,
                UserStatus.UNREVIEWED
            )),
            surname: primitives.maybeString,
            username: primitives.maybeString
        }, req.body, res)
    ) {
        return;
    }
    const userId = Number(req.params.id);
    const props = getUserProps(req);
    const isAdmin = props.role === UserRole.ADMIN;
    if (!isAdmin && props.id !== userId) {
        res.status(403).json({
            error: 'You are not authorized to access this resource.'
        });
        return;
    }
    const userRepo = Database.getRepository(User);
    const user = await userRepo.findOneBy({
        id: userId
    });
    if (!user) {
        res.status(400).json({
            error: 'Specified user does not exist.'
        });
        return;
    }
    const {
        address, email, hasAvatar, name, oid, organization, password,
        phone, role, status, surname, username
    } = req.body;
    Object.assign(user, {
        address,
        email,
        hasAvatar,
        name,
        oid,
        organization,
        phone,
        surname
    });
    if (password) {
        user.password = await bcrypt.hash(password, 10);
    }
    if (isAdmin) {
        Object.assign(user, {
            role,
            status,
            username
        });
    }
    try {
        await userRepo.save(user);
    } catch (error) {
        res.status(400).json({
            error: 'Entered user data is invalid.'
        });
        return;
    }
    res.json({
        user: extractUserInfo(user)
    });
});

router.delete('/:id', isAdminMiddleware, async function(req, res) {
    if (!validateRequest({
        id: primitives.string
    }, req.params, res)) {
        return;
    }
    const userRepo = Database.getRepository(User);
    try {
        await userRepo.delete({
            id: Number(req.params.id)
        });
        res.json({success: true});
    } catch (error) {
        res.status(400).json({
            error: 'Bad request.'
        });
    }
});

router.put(
    '/:id/profile-picture',
    isLoggedInMiddleware,
    upload.single('photo'),
    async function(req, res) {
        if (!validateRequest({
            id: primitives.string
        }, req.params, res)) {
            return;
        }
        const userId = getUserProps(req).id;
        if (userId !== Number(req.params.id)) {
            res.status(400).json({
                error: 'You are not authorized to change this profile picture.'
            });
            return;
        }
        const {file} = req;
        if (!file) {
            res.status(400).json({
                error: 'No photo specified.'
            });
            return;
        }
        const photoData = file.buffer;
        const photoSize = imageSize(photoData);
        if (
            !photoSize.width ||
            !photoSize.height ||
            photoSize.width < 100 ||
            photoSize.width > 300 ||
            photoSize.height < 100 ||
            photoSize.height > 300
        ) {
            res.status(400).json({
                error: 'Invalid image dimensions.'
            });
            return;
        }
        await writeFile(`public/profile-picture/${userId}.png`, photoData);
        res.json({success: true});
    }
);

export default router;
