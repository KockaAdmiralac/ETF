import {ApiService, UserInfo} from '../api.service';
import {Component, OnInit} from '@angular/core';
import {Router} from '@angular/router';
import {UtilService} from '../util.service';

/**
 * Component for the user management screen.
 */
@Component({
    selector: 'app-users',
    templateUrl: './users.component.html'
})
export class UsersComponent implements OnInit {
    email: string = '';
    name: string = '';
    password: string = '';
    confirmPassword: string = '';
    phone: string = '';
    surname: string = '';
    username: string = '';
    file: File | null = null;
    registrationError: string = '';
    managementError: string = '';
    address: string = '';
    oid: string = '';
    organization: string = '';
    registered: boolean = false;
    users: UserInfo[] = [];
    /**
     * Injects the API service and Angular Router.
     * @param api API service to inject
     * @param router Angular Router to inject
     * @param util Utilities service to inject
     */
    constructor(
        private api: ApiService,
        private router: Router,
        private util: UtilService
    ) { }
    /**
     * Required component initialization method.
     */
    async ngOnInit(): Promise<void> {
        if (!this.util.isAdmin()) {
            await this.util.redirectToLogin();
        }
        const {users} = await this.api.getAllUsers();
        this.users = users;
    }
    /**
     * Registers the user and sets their profile picutre.
     * @param event Event arguments
     */
    async register(event: SubmitEvent) {
        event.preventDefault();
        if (
            !this.email ||
            !this.name ||
            !this.password ||
            !this.confirmPassword ||
            !this.phone ||
            !this.surname ||
            !this.username
        ) {
            this.registrationError = 'All except the last three fields ' +
                                     'are required.';
            return;
        }
        if (this.password !== this.confirmPassword) {
            this.registrationError = 'Password and password confirmation ' +
                                     'do not match.';
            return;
        }
        if (!this.util.isValidPassword(this.password)) {
            this.registrationError = 'Password does not meet the above rules.';
            return;
        }
        if (!this.util.isValidEmail(this.email)) {
            this.registrationError = 'Entered email address is not valid.';
            return;
        }
        try {
            const avatar = new FormData();
            if (this.file) {
                avatar.append('photo', this.file);
            }
            if (!this.registered) {
                const userId = await this.api.register({
                    address: this.address,
                    avatar: this.file ? avatar : undefined,
                    email: this.email,
                    name: this.name,
                    oid: Number(this.oid || '0'),
                    organization: this.organization,
                    password: this.password,
                    phone: this.phone,
                    surname: this.surname,
                    username: this.username
                });
                await this.api.editUser(userId, {
                    role: 'organization',
                    status: 'active'
                });
            }
            this.registered = true;
            await this.router.navigate(['/account/login']);
        } catch (error: any) {
            this.registrationError = error.error.error;
        }
    }
    /**
     * Handles avatar upload.
     * @param event Event arguments
     */
    registerAvatar(event: Event) {
        this.file = (event?.currentTarget as any).files.item(0);
    }
    /**
     * Handles user deletion.
     * @param id ID of the user to delete
     */
    async deleteUser(id: number) {
        this.managementError = '';
        try {
            await this.api.deleteUser(id);
            this.users = this.users.filter(u => u.id !== id);
        } catch (error: any) {
            this.managementError = error.error.error;
        }
    }
    /**
     * Handles editing of user information.
     * @param id ID of the user edit
     */
    async editUser(id: number) {
        this.managementError = '';
        try {
            const user = this.users.find(u => u.id === id);
            if (!user) {
                return;
            }
            await this.api.editUser(id, {
                name: user.name,
                phone: user.phone,
                role: user.role,
                status: user.status,
                surname: user.surname,
                username: user.username
            });
        } catch (error: any) {
            this.managementError = error.error.error;
        }
    }
}
