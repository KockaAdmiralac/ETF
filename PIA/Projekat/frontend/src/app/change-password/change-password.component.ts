import {Component, OnInit} from '@angular/core';
import {ApiService} from '../api.service';
import {Router} from '@angular/router';
import {UtilService} from '../util.service';

/**
 * Component for the password changing screen.
 */
@Component({
    selector: 'app-change-password',
    styleUrls: ['./change-password.component.css'],
    templateUrl: './change-password.component.html'
})
export class ChangePasswordComponent implements OnInit {
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
    ngOnInit(): void { }
}
