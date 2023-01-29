import {ActivatedRoute, Router} from '@angular/router';
import {Component, OnInit} from '@angular/core';
import {ApiService} from '../api.service';
import {UtilService} from '../util.service';

/**
 * Component for the password reset screen.
 */
@Component({
    selector: 'app-reset-password',
    templateUrl: './reset-password.component.html'
})
export class ResetPasswordComponent implements OnInit {
    error: string = '';
    success: boolean = false;
    newPassword: string = '';
    confirmPassword: string = '';
    /**
     * Injects the API service and Angular Router.
     * @param api API service to inject
     * @param router Angular Router to inject
     * @param util Utilities service to inject
     * @param route Currently activated route data to inject
     */
    constructor(
        private api: ApiService,
        private router: Router,
        private util: UtilService,
        private route: ActivatedRoute
    ) { }
    /**
     * Required component initialization method.
     */
    ngOnInit(): void { }
    /**
     * Handles the reset password form submission.
     * @param event Event arguments
     */
    async resetPassword(event: SubmitEvent) {
        event.preventDefault();
        const token = this.route.snapshot.paramMap.get('token');
        if (!token) {
            this.error = 'A token has not been provided. ' +
                         'Please follow the link from the email you received.';
            return;
        }
        if (!this.newPassword || !this.confirmPassword) {
            this.error = 'Password cannot be blank.';
            return;
        }
        if (this.newPassword !== this.confirmPassword) {
            this.error = 'Password and confirmation do not match.';
            return;
        }
        if (!this.util.isValidPassword(this.newPassword)) {
            this.error = 'Password does not meet the above rules.';
            return;
        }
        try {
            await this.api.resetPassword(token, this.newPassword);
            this.success = true;
        } catch (error: any) {
            this.error = error.error.error;
        }
    }
}
