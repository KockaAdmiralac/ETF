import {Component, OnInit} from '@angular/core';
import {ApiService} from '../api.service';
import {Router} from '@angular/router';
import {UtilService} from '../util.service';

/**
 * Component for the 'forgot password' screen.
 */
@Component({
    selector: 'app-forgot-password',
    templateUrl: './forgot-password.component.html'
})
export class ForgotPasswordComponent implements OnInit {
    email: string = '';
    confirmEmail: string = '';
    error: string = '';
    status: string = '';
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
     * Handles forgot password form submission.
     * @param event Event arguments
     */
    async forgotPassword(event: SubmitEvent) {
        event.preventDefault();
        this.error = '';
        this.status = '';
        if (!this.email || !this.confirmEmail) {
            this.error = 'All fields are required.';
            return;
        }
        if (this.email !== this.confirmEmail) {
            this.error = 'Email and confirmation do not match.';
            return;
        }
        if (!this.util.isValidEmail(this.email)) {
            this.error = 'Entered email address is not valid.';
            return;
        }
        try {
            await this.api.forgotPassword(this.email);
            this.status = 'A password reset link has been sent to your ' +
                          'email, if your user account exists.';
        } catch (error: any) {
            this.error = error.error.error;
        }
    }
}
