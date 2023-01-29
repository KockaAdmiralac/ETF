import {Component} from '@angular/core';
import {UtilService} from './util.service';

/**
 * Main app component.
 */
@Component({
    selector: 'app-root',
    styleUrls: ['./app.component.css'],
    templateUrl: './app.component.html'
})
export class AppComponent {
    navVisible: boolean = false;
    /**
     * Injects various utilities into the component.
     * @param util Utilities to inject
     */
    constructor(public util: UtilService) {}
    title = 'PIA projekat';
    /**
     * Logs the user out by clearing all login data
     * and returning to the login screen.
     */
    async logout() {
        localStorage.removeItem('access-token');
        localStorage.removeItem('role');
        localStorage.removeItem('user-id');
        localStorage.removeItem('refresh-token');
        await this.util.redirectToLogin();
    }
    /**
     * Toggles navigation bar's visibility.
     */
    seeMore() {
        this.navVisible = !this.navVisible;
    }
}
