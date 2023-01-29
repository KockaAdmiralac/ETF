import {Component, OnInit} from '@angular/core';
import {Router} from '@angular/router';

/**
 * Component for the index page.
 */
@Component({
    selector: 'app-index',
    templateUrl: './index.component.html'
})
export class IndexComponent implements OnInit {
    /**
     * Injects the router into this component.
     * @param router Angular Router instance to inject
     */
    constructor(private router: Router) {}
    /**
     * Required method for Angular components.
     * Redirects to login if the user hasn't logged in, or profile
     * if they have.
     */
    ngOnInit(): void {
        if (localStorage.getItem('access-token')) {
            this.router.navigate(['/me']);
        } else {
            this.router.navigate(['/account/login']);
        }
    }
}
