import {ApiService} from '../api.service';
import {Component} from '@angular/core';
import {Router} from '@angular/router';

/**
 * Component for the librarian screen.
 */
@Component({
    selector: 'app-bibliotekar',
    templateUrl: './bibliotekar.component.html'
})
export class BibliotekarComponent {
    id: string = '';
    title: string = '';
    author: string = '';
    error: string = '';
    success: string = '';
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
    async addBook(event: Event) {
        event.preventDefault();
        this.error = '';
        this.success = '';
        if (!this.id || !this.title || !this.author) {
            this.error = 'All fields are required.';
            return;
        }
        await this.api.addBook(this.id, this.title, this.author);
        this.success = 'Added!';
    }
    /**
     * Logs the user out and redirects them to the login screen.
     */
    logout() {
        localStorage.removeItem('username');
        localStorage.removeItem('first_name');
        localStorage.removeItem('last_name');
        this.router.navigate(['/']);
    }
}
