import {Component, OnInit} from '@angular/core';
import {ApiService} from '../api.service';
import {Router} from '@angular/router';

/**
 * Component for the reader screen.
 */
@Component({
    selector: 'app-citalac',
    templateUrl: './citalac.component.html'
})
export class CitalacComponent implements OnInit {
    books: any[] = [];
    allBooks: any[] = [];
    shownBooks: any[] = [];
    username: string = '';
    firstName: string = '';
    lastName: string = '';
    title: string = '';
    author: string = '';
    /**
     * Injects the API service and Angular Router.
     * @param api API service to inject
     * @param router Angular Router to inject
     */
    constructor(private api: ApiService, private router: Router) { }
    /**
     * Runs on component initialization.
     */
    async ngOnInit(): Promise<void> {
        this.username = localStorage.getItem('username');
        this.firstName = localStorage.getItem('first_name');
        this.lastName = localStorage.getItem('last_name');
        const {books} = await this.api.getBooks(this.username);
        this.books = books;
        this.allBooks = (await this.api.getAllBooks()).books;
    }
    /**
     * Rents or returns a book depending on the status.
     * @param book Book to rent or return
     * @param status True if renting, false if returning
     */
    async changeBookStatus(book: any, status: boolean) {
        const body = {...book};
        if (status) {
            body.username = this.username;
        }
        await this.api.changeBookStatus(body);
        location.reload();
    }
    /**
     * Checks if the book deadline has passed.
     * @param book Book to check the expiration for
     * @returns Whether the book deadline has passed
     */
    isExpired(book: any) {
        return new Date(book.deadline) < new Date();
    }
    /**
     * Updates the table of books after searching.
     * @param event Event arguments
     */
    updateSearch(event?: Event) {
        if (event) {
            event.preventDefault();
        }
        this.shownBooks = this.allBooks.filter(
            b => b.title.includes(this.title) &&
                 b.author.includes(this.author)
        );
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
