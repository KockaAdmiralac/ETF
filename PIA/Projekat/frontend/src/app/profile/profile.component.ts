import {
    ApiService,
    CommentInfo,
    ThreadInfo,
    UserInfo,
    WorkshopInfo
} from '../api.service';
import {Component, OnDestroy, OnInit} from '@angular/core';
import {ActivatedRoute, Router} from '@angular/router';
import {UtilService} from '../util.service';

/**
 * Component for the user profile screen.
 */
@Component({
    selector: 'app-profile',
    styleUrls: ['./profile.component.css'],
    templateUrl: './profile.component.html'
})
export class ProfileComponent implements OnInit, OnDestroy {
    address: string = '';
    confirmPassword: string = '';
    email: string = '';
    name: string = '';
    oid: string = '';
    organization: string = '';
    password: string = '';
    phone: string = '';
    surname: string = '';
    username: string = '';
    updateProfileError: string = '';
    updateProfileSuccess: string = '';
    user?: UserInfo;
    id: number = 0;
    cachebuster: number = 0;
    workshops: WorkshopInfo[] = [];
    comments: CommentInfo[] = [];
    likes: WorkshopInfo[] = [];
    threads: ThreadInfo[] = [];
    openThreads: ThreadInfo[] = [];
    messages: string[] = [];
    interval?: NodeJS.Timer;
    /**
     * Injects the API service and Angular Router.
     * @param api API service to inject
     * @param router Angular Router to inject
     * @param route Current route to inject
     * @param util Utilities service to inject
     */
    constructor(
        private api: ApiService,
        private router: Router,
        private route: ActivatedRoute,
        public util: UtilService
    ) {}
    /**
     * Required component initialization method.
     */
    async ngOnInit(): Promise<void> {
        if (!this.util.isLoggedIn()) {
            await this.util.redirectToLogin();
        }
        const {
            comments,
            email,
            likes,
            threads,
            user
        } = await this.api.getUser();
        this.comments = comments;
        this.likes = likes;
        this.threads = threads;
        this.user = user;
        this.id = Number(localStorage.getItem('user-id'));
        if (this.user) {
            this.address = user.address;
            this.email = email;
            this.name = user.name;
            this.oid = user.oid;
            this.organization = user.organization || '';
            this.phone = user.phone;
            this.surname = user.surname;
            this.username = user.username;
        }
        const {signups, workshops} = await this.api.getAllWorkshops();
        this.workshops = workshops.filter(
            (w: WorkshopInfo) => signups.includes(w.id)
        );
        this.interval = setInterval(this.refreshMessages.bind(this), 1000);
        this.route.fragment.subscribe(this.openThreadFromFragment.bind(this));
    }
    /**
     * Opens a thread when a fragment change is detected.
     * @param fragment Fragment of the URL representing the thread ID
     */
    openThreadFromFragment(fragment: string | null) {
        const threadId = Number(fragment);
        const thread = this.threads.find(t => t.id === threadId);
        if (thread) {
            this.openThread(thread);
        }
    }
    /**
     * Called when the component is unmounting.
     */
    ngOnDestroy() {
        if (this.interval) {
            clearInterval(this.interval);
        }
    }
    /**
     * Handles profile form submission.
     * @param event Submit event arguments
     */
    async updateProfile(event: SubmitEvent) {
        event.preventDefault();
        this.updateProfileError = '';
        this.updateProfileSuccess = '';
        if (this.password !== this.confirmPassword) {
            this.updateProfileError = 'Password and confirmation do not match.';
            return;
        }
        if (this.password && !this.util.isValidPassword(this.password)) {
            this.updateProfileError = 'Invalid password format.';
            return;
        }
        if (!this.util.isValidEmail(this.email)) {
            this.updateProfileError = 'Invalid email.';
            return;
        }
        await this.api.editUser(this.id, {
            address: this.address || undefined,
            email: this.email,
            name: this.name,
            oid: this.oid ? Number(this.oid) : undefined,
            organization: this.organization || undefined,
            password: this.password || undefined,
            phone: this.phone,
            surname: this.surname
        });
        this.updateProfileSuccess = 'Profile successfully updated.';
        if (this.password) {
            localStorage.removeItem('access-token');
            localStorage.removeItem('role');
            localStorage.removeItem('user-id');
            localStorage.removeItem('refresh-token');
            await this.util.redirectToLogin();
        }
    }
    /**
     * Handles avatar changes.
     * @param event Event arguments
     */
    async updateAvatarFile(event: Event) {
        const file = (event?.currentTarget as any).files.item(0);
        if (!file) {
            return;
        }
        const fd = new FormData();
        fd.append('photo', file);
        try {
            await this.api.updateAvatar(fd);
            await this.api.editUser(this.id, {
                hasAvatar: true
            });
            if (this.user) {
                this.user.hasAvatar = true;
                ++this.cachebuster;
            }
        } catch (error: any) {
            this.updateProfileError = error.error.error;
        }
    }
    /**
     * Sorts workshops by the specified property.
     * @param property Property to sort by
     */
    sortBy(property: 'name' | 'date' | 'place' | 'snippet') {
        this.workshops = this.workshops
            .sort((w1, w2) => w1[property]
                .toString()
                .localeCompare(w2[property].toString()));
    }
    /**
     * Handles workshop disliking from the audit log.
     * @param workshop Workshop data
     */
    async dislike(workshop: WorkshopInfo) {
        await this.api.removeLike(workshop.id);
        this.likes = this.likes.filter(w => w.id !== workshop.id);
    }
    /**
     * Handles comment editing from the audit log.
     * @param comment Comment data
     */
    async editComment(comment: CommentInfo) {
        if (!comment.workshop) {
            return;
        }
        await this.api.editComment(
            comment.workshop.id,
            comment.id,
            comment.text
        );
    }
    /**
     * Handles comment deletion from the audit log.
     * @param comment Comment data
     */
    async deleteComment(comment: CommentInfo) {
        if (!comment.workshop) {
            return;
        }
        await this.api.deleteComment(comment.workshop.id, comment.id);
        this.comments = this.comments.filter(c => c.id !== comment.id);
    }
    /**
     * Opens a thread in the right messages pane.
     * @param thread Thread to open
     */
    openThread(thread: ThreadInfo) {
        if (!this.openThreads.includes(thread)) {
            this.openThreads.push(thread);
        }
    }
    /**
     * Handles message sending.
     * @param thread Thread to send messages to
     */
    async sendMessage(thread: ThreadInfo) {
        const text = this.messages[thread.id] || '';
        if (!text) {
            return;
        }
        const {message} = await this.api.sendMessage(thread.id, text);
        thread.messages.push(message);
    }
    /**
     * Refreshes messages in currently open threads.
     */
    async refreshMessages() {
        for (const thread of this.openThreads) {
            const {messages} = await this.api.getMessages(thread.id);
            thread.messages = messages;
        }
    }
}
