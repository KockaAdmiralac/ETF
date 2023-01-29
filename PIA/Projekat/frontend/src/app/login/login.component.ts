import {Component, OnInit} from '@angular/core';
import {ApiService} from '../api.service';
import {Router} from '@angular/router';
import {UtilService} from '../util.service';

/**
 * Component for the login screen.
 */
@Component({
    selector: 'app-login',
    templateUrl: './login.component.html'
})
export class LoginComponent implements OnInit {
    username: string = '';
    password: string = '';
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
    ngOnInit(): void {
        if (this.util.isLoggedIn()) {
            this.router.navigate(['/me']);
        }
    }
    /**
     * Callback after submitting the login form.
     * @param event DOM event to intercept
     */
    async login(event: SubmitEvent) {
        event.preventDefault();
        if (!this.username || !this.password) {
            this.error = 'All fields are required.';
            return;
        }
        try {
            await this.api.login(this.username, this.password, true);
            this.router.navigate(['/me']);
        } catch (error: any) {
            this.error = error.error.error;
        }
    }
}
