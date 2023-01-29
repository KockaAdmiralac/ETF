import User, {UserRole, UserStatus} from '../entities/User';
import Comment from '../entities/Comment';
import Message from '../entities/Message';
import Thread from '../entities/Thread';
import Workshop from '../entities/Workshop';

export interface UserInfo {
    id: number;
    username: string;
    name: string;
    surname: string;
    phone: string;
    organization?: string;
    address?: string;
    oid?: number;
    role: UserRole;
    status: UserStatus;
    hasAvatar: boolean;
}

export interface WorkshopInfo {
    id: number;
    name: string;
    date: Date;
    place: string;
    latitude: number;
    longitude: number;
    description: string;
    snippet: string;
    photos: number[];
    numLikes: number;
    numComments: number;
    user: UserInfo;
    active: boolean;
    capacity: number;
}

export interface CommentInfo {
    date: Date,
    id: number;
    text: string;
    user: UserInfo;
    workshop?: WorkshopInfo;
}

export interface MessageInfo {
    id: number;
    text: string;
    user: UserInfo;
    date: Date;
}

export interface ThreadInfo {
    id: number;
    workshop: WorkshopInfo;
    user: UserInfo;
    messages: MessageInfo[];
}

export const extractUserInfo = (user: User): UserInfo => ({
    address: user.address,
    hasAvatar: user.hasAvatar,
    id: user.id,
    name: user.name,
    oid: user.oid,
    organization: user.organization,
    phone: user.phone,
    role: user.role,
    status: user.status,
    surname: user.surname,
    username: user.username
});

export const extractWorkshopInfo = (workshop: Workshop): WorkshopInfo => ({
    active: workshop.active,
    capacity: workshop.capacity,
    date: workshop.date,
    description: workshop.description,
    id: workshop.id,
    latitude: workshop.latitude,
    longitude: workshop.longitude,
    name: workshop.name,
    numComments: workshop.comments.length,
    numLikes: workshop.likedUsers.length,
    photos: workshop.photos.map(photo => photo.id),
    place: workshop.place,
    snippet: workshop.snippet,
    user: extractUserInfo(workshop.user)
});

export const extractCommentInfo = (
    comment: Comment,
    workshopInfo: boolean = false
): CommentInfo => ({
    date: comment.date,
    id: comment.id,
    text: comment.text,
    user: extractUserInfo(comment.user),
    workshop: workshopInfo && comment.workshop ?
        extractWorkshopInfo(comment.workshop) :
        undefined
});

export const extractMessageInfo = (message: Message): MessageInfo => ({
    date: message.date,
    id: message.id,
    text: message.text,
    user: extractUserInfo(message.user)
});

export const extractThreadInfo = (thread: Thread): ThreadInfo => ({
    id: thread.id,
    messages: thread.messages.map(extractMessageInfo),
    user: extractUserInfo(thread.user),
    workshop: extractWorkshopInfo(thread.workshop)
});
