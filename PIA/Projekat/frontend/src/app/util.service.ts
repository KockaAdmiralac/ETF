import {API_URL, UserInfo} from './api.service';
import {Injectable} from '@angular/core';
import {Router} from '@angular/router';

type UserRole = 'admin' | 'basic' | 'organization' | 'logged-out';

/**
 * Service for various utilities within the application.
 */
@Injectable({
    providedIn: 'root'
})
export class UtilService {
    /**
     * Injects the Angular Router.
     * @param router Angular Router to inject
     */
    constructor(private router: Router) { }
    /**
     * Redirects the user to the login screen.
     * @returns Promise that resolves upon navigation
     */
    redirectToLogin() {
        return this.router.navigate(['/account/login']);
    }
    /**
     * Returns the user's role.
     * @returns The user's role as a string
     */
    getUserRole(): UserRole {
        const lsRole = localStorage.getItem('role');
        if (lsRole === 'admin') {
            return 'admin';
        } else if (lsRole === 'basic') {
            return 'basic';
        } else if (lsRole === 'organization') {
            return 'organization';
        }
        return 'logged-out';
    }
    /**
     * Checks whether the user is an administrator.
     * @returns True if the user is an administrator
     */
    isAdmin(): boolean {
        return this.getUserRole() === 'admin';
    }
    /**
     * Checks whether the user is allowed to make changes to workshops.
     * @returns True if the user is an organizer or administrator.
     */
    isOrganization(): boolean {
        return this.getUserRole() === 'organization' || this.isAdmin();
    }
    /**
     * Checks if the user is logged in.
     * @returns True, if the user is logged in
     */
    isLoggedIn() {
        return this.getUserRole() !== 'logged-out';
    }
    /**
     * Checks whether an email address is valid.
     * @param email Email address to check
     * @returns True if the email address is valid
     */
    isValidEmail(email: string): boolean {
        return /^[^\s@]+@[^\s@]+\.[^\s@]+$/u.test(email);
    }
    /**
     * Checks whether the password meets the required password
     * guidelines.
     * @param password Password to check
     * @returns Whether the password is valid
     */
    isValidPassword(password: string): boolean {
        return password.length >= 8 &&
               password.length <= 16 &&
               /[A-Z]/u.test(password) &&
               /[a-z]/u.test(password) &&
               /[0-9]/u.test(password) &&
               /[^a-zA-Z0-9]/u.test(password) &&
               /^[a-zA-Z]/u.test(password);
    }
    /**
     * Returns the URL of a workshop photo given its ID.
     * @param id ID of the photo
     * @returns Workshop photo URL
     */
    photoUrl(id: number): string {
        return `${API_URL}/upload/${id}.png`;
    }
    /**
     * Returns the URL to a user's profile picture.
     * @param user User whose profile picture URL should be returned
     * @returns User's profile picture URL
     */
    profilePictureUrl(user: UserInfo) {
        if (user.hasAvatar) {
            return `${API_URL}/profile-picture/${user.id}.png`;
        }
        return '/assets/default.png';
    }
    /**
     * Returns the user ID if the user is logged in, or 0 if
     * they are not.
     * @returns User ID
     */
    getUserId(): number {
        return Number(localStorage.getItem('user-id') || '0');
    }
}
