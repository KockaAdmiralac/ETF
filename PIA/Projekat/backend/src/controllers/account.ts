import User, {UserRole, UserStatus} from '../entities/User';
import {
    UserProps,
    getAccessToken,
    getRefreshToken,
    getUserProps,
    isAdmin,
    isLoggedInRefreshMiddleware
} from '../util/auth';
import {Database} from '../util/database';
import {Router} from 'express';
import bcrypt from 'bcrypt';
import config from '../../config.json';
import {extractUserInfo} from '../util/transform';
import {primitives} from '@altostra/type-validations';
import {randomBytes} from 'crypto';
import {sendEmail} from '../util/email';
import {validateRequest} from '../util/validation';

const router = Router();

/**
 * Turns a user row from database into properties to use in the JWT.
 * @param user User from the database
 * @returns Properties in the JWT
 */
function propsFromUser(user: User): UserProps {
    const {id, email, role, username} = user;
    return {
        email,
        id,
        role,
        username
    };
}

const isValidEmail = (email: string): boolean => /^[^\s@]+@[^\s@]+\.[^\s@]+$/u.test(email);

router.post('/login', async function(req, res) {
    if (!validateRequest({
        admin: primitives.maybeBoolean,
        password: primitives.string,
        username: primitives.string
    }, req.body, res)) {
        return;
    }
    const {admin, username, password} = req.body;
    const user = await Database.getRepository(User).findOneBy({username});
    if (!user || !admin && user.role === UserRole.ADMIN) {
        res.status(400).json({
            error: 'Invalid username or password.'
        });
        return;
    }
    if (!await bcrypt.compare(password, user.password)) {
        res.status(400).json({
            error: 'Invalid username or password.'
        });
        return;
    }
    if (user.status !== UserStatus.ACTIVE) {
        res.status(400).json({
            error: 'User account is not active. ' +
                   'Please wait for an administrator to activate your account.'
        });
        return;
    }
    const props = propsFromUser(user);
    const accessToken = getAccessToken(props);
    const refreshToken = getRefreshToken(props);
    res.json({
        accessToken,
        refreshToken,
        user: extractUserInfo(user)
    });
});

router.post('/refresh', isLoggedInRefreshMiddleware, async function(req, res) {
    const {id} = getUserProps(req);
    const user = await Database.getRepository(User).findOneBy({id});
    if (!user) {
        res.status(400).json({
            error: 'User account no longer exists.'
        });
        return;
    }
    const props = propsFromUser(user);
    const accessToken = getAccessToken(props);
    res.json({accessToken});
});

router.post('/register', async function(req, res) {
    if (!validateRequest({
        address: primitives.maybeString,
        email: primitives.string,
        hasAvatar: primitives.boolean,
        name: primitives.string,
        oid: primitives.maybeNumber,
        organization: primitives.maybeString,
        password: primitives.string,
        phone: primitives.string,
        surname: primitives.string,
        username: primitives.string
    }, req.body, res)) {
        return;
    }
    if (!isValidEmail(req.body.email)) {
        res.status(400).json({
            error: 'Invalid email format.'
        });
        return;
    }
    const user = new User();
    Object.assign(user, req.body);
    user.role = UserRole.BASIC;
    user.status = UserStatus.UNREVIEWED;
    if ('auth' in req && isAdmin(req)) {
        user.role = UserRole.ORGANIZATION;
        user.status = UserStatus.ACTIVE;
    }
    user.password = await bcrypt.hash(user.password, 10);
    try {
        await Database.getRepository(User).insert(user);
        const props = propsFromUser(user);
        const accessToken = getAccessToken(props);
            res.json({
                accessToken,
                success: true,
                user: extractUserInfo(user)
        });
    } catch (error: any) {
        if (
            error &&
            typeof error === 'object' &&
            typeof error.code === 'string' &&
            error.code === 'ER_DUP_ENTRY'
        ) {
            res.status(400).json({
                error: 'User with given data already exists.'
            });
        } else {
            throw error;
        }
    }
});

router.post('/forgot-password', async function(req, res) {
    if (!validateRequest({
        email: primitives.string
    }, req.body, res)) {
        return;
    }
    res.json({success: true});
    const userRepo = Database.getRepository(User);
    const user = await userRepo.findOneBy({
        email: req.body.email
    });
    if (user) {
        const token = randomBytes(32).toString('hex');
        user.passwordResetToken = token;
        user.passwordResetIssuedAt = new Date();
        await userRepo.save(user);
        sendEmail('forgot-password', {
            url: `${config.frontendUrl}/account/forgot-password/${token}`
        }, user.email, 'Forgotten password');
    }
});

router.post('/forgot-password/:token', async function(req, res) {
    if (
        !validateRequest({
            token: primitives.string
        }, req.params, res) ||
        !validateRequest({
            password: primitives.string
        }, req.body, res)
    ) {
        return;
    }
    const userRepo = Database.getRepository(User);
    const user = await userRepo.findOneBy({
        passwordResetToken: req.params.token
    });
    if (!user) {
        res.status(400).json({
            error: 'Invalid password reset token.'
        });
        return;
    }
    const currentTime = new Date().getTime();
    const expiryTime = user.passwordResetIssuedAt?.getTime() || 0;
    const expiryTimeDelta = currentTime - expiryTime;
    if (expiryTimeDelta > 30 * 60 * 1000) {
        res.status(400).json({
            error: 'Password reset token expired.'
        });
        return;
    }
    user.passwordResetIssuedAt = null;
    user.passwordResetToken = null;
    user.password = await bcrypt.hash(req.body.password, 10);
    await userRepo.save(user);
    res.json({success: true});
});

export default router;
