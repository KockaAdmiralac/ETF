import {HttpClient} from '@angular/common/http';
import {Injectable} from '@angular/core';

const API_URL = 'http://localhost:4000';

/**
 * Service for communicating with the API.
 */
@Injectable({
    providedIn: 'root'
})
export class ApiService {
    /**
     * Injects the HTTP client.
     * @param client HTTP client to inject
     */
    constructor(private client: HttpClient) { }
    /**
     * Logs the user in.
     * @param username User's username
     * @param password User's password
     * @param type User's type
     * @returns User data
     */
    login(username: string, password: string, type: string): Promise<any> {
        return this.client.post(`${API_URL}/login`, {
            password,
            type,
            username
        }).toPromise();
    }
    /**
     * Retrieves user's books rented from the library.
     * @param username User's username
     * @returns Book data about rented books
     */
    getBooks(username: string): Promise<any> {
        return this.client.get(`${API_URL}/citalac?username=${encodeURIComponent(username)}`).toPromise();
    }
    /**
     * Retrieves all books available in the library.
     * @returns Book data about all books
     */
    getAllBooks(): Promise<any> {
        return this.client.get(`${API_URL}/citalac`).toPromise();
    }
    /**
     * Rents or returns a book.
     * @param book Book to rent or return
     * @returns API response data
     */
    changeBookStatus(book: any) {
        return this.client.post(`${API_URL}/citalac`, book).toPromise();
    }
    /**
     * Adds a new book to the library's database.
     * @param id ID of the new book
     * @param title Title of the new book
     * @param author Author of the new book
     * @returns API response data
     */
    addBook(id: string, title: string, author: string): Promise<any> {
        return this.client.post(`${API_URL}/bibliotekar`, {
            author,
            id,
            title
        }).toPromise();
    }
}
