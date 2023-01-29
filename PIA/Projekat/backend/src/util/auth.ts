import {Request, Response} from 'express';
import User, {UserRole} from '../entities/User';
import {Database} from './database';
import config from '../../config.json';
import {expressjwt} from 'express-jwt';
import {sign} from 'jsonwebtoken';

const {secret} = config;
export const jwt = expressjwt({
    algorithms: ['HS256'],
    credentialsRequired: false,
    secret
});

export interface UserProps {
    email: string;
    id: number;
    role: UserRole;
    username: string;
}

/**
 * Express middleware for verifying the user belongs to one of the specified
 * roles.
 * @param roles Roles the user must belong to
 * @param allowRefresh Whether the token can be a refresh token
 * @param req Request data
 * @param res Response data
 * @param next Function to call next middleware with
 */
export function verifyRoles(
    roles: string[],
    allowRefresh: boolean,
    req: Request,
    res: Response,
    next: () => void
) {
    jwt(req, res, function() {
        if (!('auth' in req)) {
            res.status(401).json({
                error: 'User is not authenticated.'
            });
            return;
        }
        const {refresh, role} = (req as any).auth;
        const refreshDisallowed = Boolean(refresh) !== allowRefresh;
        if (roles.includes(role) && !refreshDisallowed) {
            return next();
        }
        res.status(403).json({
            error: 'User is not authorized to access this resource.'
        });
    });
}

export const isOrganization = (req: Request): boolean => [
    'organization',
    'admin'
].includes((req as any).auth.role);

export const isAdmin = (req: Request): boolean => (req as any)
    .auth
    .role === 'admin';

export const isLoggedInMiddleware = (
    req: Request,
    res: Response,
    next: () => void
) => verifyRoles(['basic', 'organization', 'admin'], false, req, res, next);

export const isLoggedInRefreshMiddleware = (
    req: Request,
    res: Response,
    next: () => void
) => verifyRoles(['basic', 'organization', 'admin'], true, req, res, next);

export const isOrganizationMiddleware = (
    req: Request,
    res: Response,
    next: () => void
) => verifyRoles(['organization', 'admin'], false, req, res, next);

export const isAdminMiddleware = (
    req: Request,
    res: Response,
    next: () => void
) => verifyRoles(['admin'], false, req, res, next);

export const getAccessToken = (props: object) => sign(props, config.secret, {
    expiresIn: '5 minutes'
});

export const getRefreshToken = (props: object) => sign({
    ...props,
    refresh: true
}, config.secret, {
    expiresIn: '30 days'
});

export const getUserProps = (req: Request): UserProps => (req as any).auth;

export const getCurrentUser = (req: Request): Promise<User | null> => Database
    .getRepository(User)
    .findOneBy({
        id: getUserProps(req).id
    });
