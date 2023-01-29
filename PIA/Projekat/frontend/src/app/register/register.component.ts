import {Component, OnInit} from '@angular/core';
import {ApiService} from '../api.service';
import {Router} from '@angular/router';
import {UtilService} from '../util.service';

/**
 * Component for the user registration screen.
 */
@Component({
    selector: 'app-register',
    templateUrl: './register.component.html'
})
export class RegisterComponent implements OnInit {
    email: string = '';
    name: string = '';
    password: string = '';
    confirmPassword: string = '';
    phone: string = '';
    surname: string = '';
    username: string = '';
    file: File | null = null;
    error: string = '';
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
        if (this.util.isLoggedIn()) {
            await this.router.navigate(['/me']);
        }
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
            this.error = 'All fields are required.';
            return;
        }
        if (this.password !== this.confirmPassword) {
            this.error = 'Password and password confirmation do not match.';
            return;
        }
        if (!this.util.isValidPassword(this.password)) {
            this.error = 'Password does not meet the above rules.';
            return;
        }
        if (!this.util.isValidEmail(this.email)) {
            this.error = 'Entered email address is not valid.';
            return;
        }
        try {
            const avatar = new FormData();
            if (this.file) {
                avatar.append('photo', this.file);
            }
            await this.api.register({
                avatar: this.file ? avatar : undefined,
                email: this.email,
                name: this.name,
                password: this.password,
                phone: this.phone,
                surname: this.surname,
                username: this.username
            });
            await this.router.navigate(['/account/login']);
        } catch (error: any) {
            this.error = error.error.error;
        }
    }
    /**
     * Handles avatar upload.
     * @param event Event arguments
     */
    registerAvatar(event: Event) {
        this.file = (event?.currentTarget as any).files.item(0);
    }
}
