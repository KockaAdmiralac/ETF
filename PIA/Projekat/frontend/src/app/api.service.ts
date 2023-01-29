import {HttpClient} from '@angular/common/http';
import {Injectable} from '@angular/core';

export const API_URL = 'http://localhost:4000';

type UserRole = 'admin' | 'basic' | 'organization';
type UserStatus = 'active' | 'inactive' | 'unreviewed';

interface RegistrationData {
    address?: string;
    avatar?: FormData,
    email: string;
    name: string;
    oid?: number;
    organization?: string;
    password: string;
    phone: string;
    surname: string;
    username: string
}

interface WorkshopCreationData {
    name: string;
    date: Date;
    place: string;
    latitude: number;
    longitude: number;
    capacity: number;
    description: string;
    snippet: string;
    photos: FormData | number[];
}

interface UserEditData {
    address?: string;
    avatar?: FormData,
    email?: string;
    hasAvatar?: boolean;
    name?: string;
    oid?: number;
    organization?: string;
    password?: string;
    phone?: string;
    role?: UserRole;
    status?: UserStatus;
    surname?: string;
    username?: string;
}

interface WorkshopEditData {
    active?: boolean;
    capacity?: number;
    date?: string;
    description?: string;
    latitude?: number;
    longitude?: number;
    name?: string;
    place?: string;
    snippet?: string;
    photos?: FormData | number[];
}

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
}

export interface CommentInfo {
    date: Date;
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

/**
 * Service for accessing all API-related methods.
 */
@Injectable({
    providedIn: 'root'
})
export class ApiService {
    accessToken?: string;
    refreshToken?: string;
    refreshInterval?: number;
    userId?: number;
    /**
     * Constructor used for injection.
     * @param client HTTP client to use within the service
     */
    constructor(private client: HttpClient) {
        this.accessToken = localStorage.getItem('access-token') || undefined;
        this.refreshToken = localStorage.getItem('refresh-token') || undefined;
        if (this.accessToken) {
            this.refreshInterval = window.setInterval(
                this.doRefresh.bind(this),
                60 * 1000
            );
            this.userId = Number(localStorage.getItem('user-id'));
            this.doRefresh();
        }
    }
    /**
     * Returns the most common HTTP options used in the client.
     * @returns Options used by Angular's HTTP client
     */
    private getOptions() {
        return this.accessToken ? {
            headers: {
                Authorization: `Bearer ${this.accessToken || ''}`
            },
            withCredentials: true
        } : {};
    }
    /**
     * Refreshes the user's access token.
     */
    private async doRefresh() {
        const response = await (this.client.post(`${API_URL}/account/refresh`, {}, {
            headers: {
                Authorization: `Bearer ${this.refreshToken || ''}`
            },
            withCredentials: true
        }).toPromise() as Promise<any>);
        const {accessToken} = response;
        this.accessToken = accessToken;
        localStorage.setItem('access-token', accessToken);
    }
    /**
     * Logs the user in.
     * @param username User's username
     * @param password User's password
     * @param admin Whether we are logging in an administrator
     */
    async login(username: string, password: string, admin: boolean) {
        const response = await (this.client.post(`${API_URL}/account/login`, {
            admin,
            password,
            username
        }, this.getOptions()).toPromise() as Promise<any>);
        const {accessToken, refreshToken, user} = response;
        localStorage.setItem('access-token', accessToken);
        localStorage.setItem('refresh-token', refreshToken);
        localStorage.setItem('role', user.role);
        localStorage.setItem('user-id', user.id);
        this.accessToken = accessToken;
        this.refreshToken = refreshToken;
        this.userId = user.id;
        this.refreshInterval = window.setInterval(
            this.doRefresh.bind(this),
            60 * 1000
        );
    }
    /**
     * Registers a user account.
     * @param data User information
     */
    async register(data: RegistrationData): Promise<number> {
        const {accessToken, user} = await (this.client.post(
            `${API_URL}/account/register`,
            {
                ...data,
                hasAvatar: Boolean(data.avatar)
            },
            this.getOptions()
        ).toPromise() as Promise<any>);
        if (data.avatar) {
            const prevAccessToken = this.accessToken;
            const prevUserId = this.userId;
            this.accessToken = accessToken;
            this.userId = user.id;
            try {
                await this.updateAvatar(data.avatar);
            } finally {
                this.accessToken = prevAccessToken;
                this.userId = prevUserId;
            }
        }
        return user.id;
    }
    /**
     * Updates a user's avatar.
     * @param avatar File to upload as an avatar
     * @returns API response data
     */
    updateAvatar(avatar: FormData): Promise<any> {
        return this.client.put(
            `${API_URL}/user/${this.userId}/profile-picture`,
            avatar,
            this.getOptions()
        ).toPromise();
    }
    /**
     * Requests a password reset link to be sent to the user's email address.
     * @param email Email address to reset the password to
     * @returns API response data
     */
    forgotPassword(email: string): Promise<any> {
        return this.client.post(
            `${API_URL}/account/forgot-password`,
            {email},
            this.getOptions()
        ).toPromise();
    }
    /**
     * Resets the user's password using a provided token.
     * @param token Reset password token
     * @param password Password to change to
     * @returns API response data
     */
    resetPassword(token: string, password: string): Promise<any> {
        return this.client.post(
            `${API_URL}/account/forgot-password/${token}`,
            {password},
            this.getOptions()
        ).toPromise();
    }
    /**
     * Retrieves information about all workshops.
     * @returns API response data
     */
    getAllWorkshops(): Promise<any> {
        return this.client.get(
            `${API_URL}/workshop`,
            this.getOptions()
        ).toPromise();
    }
    /**
     * Retrieves information about all workshops.
     * @returns API response data
     */
    getAllUsers(): Promise<any> {
        return this.client.get(
            `${API_URL}/user`,
            this.getOptions()
        ).toPromise();
    }
    /**
     * Retrieves information about a single workshop.
     * @param id Workshop ID
     * @returns Workshop information
     */
    getWorkshop(id: number): Promise<any> {
        return this.client.get(
            `${API_URL}/workshop/${id}`,
            this.getOptions()
        ).toPromise();
    }
    /**
     * Creates a workshop.
     * @param data Data supplied during workshop creation
     */
    async createWorkshop(data: WorkshopCreationData): Promise<WorkshopInfo> {
        const {workshop} = await (this.client.post(
            `${API_URL}/workshop`,
            data,
            this.getOptions()
        ).toPromise() as Promise<any>);
        try {
            if (Array.isArray(data.photos)) {
                await this.editWorkshop(workshop.id, {
                    photos: data.photos
                });
            } else {
                await this.addGalleryImages(workshop.id, data.photos);
            }
        } catch (error) {
            // Ignore... otherwise we will be creating a duplicate workshop
        }
        return workshop;
    }
    /**
     * Adds images to the gallery of a specified workshop.
     * @param id Workshop ID
     * @param photos Photos to add
     * @returns API response data
     */
    addGalleryImages(id: number, photos: FormData): Promise<any> {
        return this.client.post(
            `${API_URL}/workshop/${id}/photos`,
            photos,
            this.getOptions()
        ).toPromise();
    }
    /**
     * Edits specified user data.
     * @param id ID of the user to edit
     * @param data Data to edit
     * @returns API response data
     */
    async editUser(id: number, data: UserEditData) {
        const response = await this.client.patch(
            `${API_URL}/user/${id}`,
            data,
            this.getOptions()
        ).toPromise();
        if (data.avatar) {
            await this.updateAvatar(data.avatar);
        }
        return response;
    }
    /**
     * Deletes a specified user.
     * @param id ID of the user to delete
     * @returns API response data
     */
    deleteUser(id: number) {
        return this.client.delete(
            `${API_URL}/user/${id}`,
            this.getOptions()
        ).toPromise();
    }
    /**
     * Deletes a specified workshop.
     * @param id ID of the workshop to delete
     * @returns API response data
     */
    deleteWorkshop(id: number) {
        return this.client.delete(
            `${API_URL}/workshop/${id}`,
            this.getOptions()
        ).toPromise();
    }
    /**
     * Edits specified workshop data.
     * @param id ID of the workshop to edit
     * @param data Data that should be changed
     */
    async editWorkshop(id: number, data: WorkshopEditData) {
        await this.client.patch(
            `${API_URL}/workshop/${id}`,
            data,
            this.getOptions()
        ).toPromise();
        if (data.photos && !Array.isArray(data.photos)) {
            await this.addGalleryImages(id, data.photos);
        }
    }
    /**
     * Retrieves information about the current user.
     * @returns Current user information
     */
    getUser(): Promise<any> {
        return this.client.get(`${API_URL}/user/${this.userId}`, this.getOptions()).toPromise();
    }
    /**
     * Signs up for a workshop.
     * @param workshop Workshop ID
     * @returns API response data
     */
    signUp(workshop: number): Promise<any> {
        return this.client.put(`${API_URL}/workshop/${workshop}/users`, {}, this.getOptions()).toPromise();
    }
    /**
     * Cancels a signup for a workshop.
     * @param workshop Workshop ID
     * @returns API response data
     */
    cancelSignup(workshop: number): Promise<any> {
        return this.client.delete(`${API_URL}/workshop/${workshop}/users`, this.getOptions()).toPromise();
    }
    /**
     * Comments on a specified workshop.
     * @param workshop Workshop ID
     * @param text Comment text
     * @returns API response data
     */
    addComment(workshop: number, text: string): Promise<any> {
        return this.client.put(`${API_URL}/workshop/${workshop}/comments`, {text}, this.getOptions()).toPromise();
    }
    /**
     * Likes a workshop.
     * @param workshop Workshop ID
     * @returns API response data
     */
    addLike(workshop: number) {
        return this.client.put(`${API_URL}/workshop/${workshop}/likes`, {}, this.getOptions()).toPromise();
    }
    /**
     * Dislikes a workshop.
     * @param workshop Workshop ID
     * @returns API response data
     */
    removeLike(workshop: number) {
        return this.client.delete(`${API_URL}/workshop/${workshop}/likes`, this.getOptions()).toPromise();
    }
    /**
     * Edits a comment.
     * @param workshop Workshop ID where the comment was left
     * @param id Comment ID
     * @param text New comment text
     * @returns API response data
     */
    editComment(workshop: number, id: number, text: string) {
        return this.client.patch(`${API_URL}/workshop/${workshop}/comments/${id}`, {text}, this.getOptions()).toPromise();
    }
    /**
     * Deletes a comment.
     * @param workshop Workshop ID where the comment was left
     * @param id Comment ID
     * @returns API response data
     */
    deleteComment(workshop: number, id: number) {
        return this.client.delete(`${API_URL}/workshop/${workshop}/comments/${id}`, this.getOptions()).toPromise();
    }
    /**
     * Starts a new thread for a workshop.
     * @param workshop Workshop ID
     * @returns API response data
     */
    startThread(workshop: number): Promise<any> {
        return this.client.post(`${API_URL}/workshop/${workshop}/new-thread`, {}, this.getOptions()).toPromise();
    }
    /**
     * Accepts a signup for a workshop.
     * @param workshop Workshop ID
     * @param user User ID
     * @returns API response data
     */
    acceptSignup(workshop: number, user: number) {
        return this.client.post(`${API_URL}/workshop/${workshop}/signup/${user}`, {}, this.getOptions()).toPromise();
    }
    /**
     * Sends a message to a thread.
     * @param thread Thread ID
     * @param text Message to send
     * @returns API response data
     */
    sendMessage(thread: number, text: string): Promise<any> {
        return this.client.post(`${API_URL}/thread/${thread}/messages`, {text}, this.getOptions()).toPromise();
    }
    /**
     * Retrieves messages from a thread.
     * @param thread Thread ID
     * @returns API response data
     */
    getMessages(thread: number): Promise<any> {
        return this.client.get(`${API_URL}/thread/${thread}/messages`, this.getOptions()).toPromise();
    }
}
