import {ApiService} from '../api.service';
import {Component} from '@angular/core';
import {Router} from '@angular/router';

/**
 * Component for the login screen.
 */
@Component({
    selector: 'app-login',
    templateUrl: './login.component.html'
})
export class LoginComponent {
    username: string = '';
    password: string = '';
    type: string = 'citalac';
    error: string = '';
    /**
     * Injects the API service and Angular Router.
     * @param api API service to inject
     * @param router Angular Router to inject
     */
    constructor(private api: ApiService, private router: Router) { }
    /**
     * Handles form submission.
     * @param event Event arguments
     */
    async login(event: Event) {
        event.preventDefault();
        if (!this.username || !this.password || !this.type) {
            this.error = 'All fields are required.';
            return;
        }
        try {
            const {
                user
            } = await this.api.login(this.username, this.password, this.type);
            localStorage.setItem('username', user.username);
            localStorage.setItem('first_name', user.first_name);
            localStorage.setItem('last_name', user.last_name);
            this.router.navigate([`/${user.type}`]);
        } catch (error: any) {
            this.error = error.error.error;
        }
    }
}
