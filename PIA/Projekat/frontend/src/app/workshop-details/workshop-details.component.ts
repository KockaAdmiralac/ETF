import {ActivatedRoute, Router} from '@angular/router';
import {ApiService, CommentInfo, WorkshopInfo} from '../api.service';
import {Component, OnInit} from '@angular/core';
import {UtilService} from '../util.service';

/**
 * Component for the workshop details screen.
 */
@Component({
    selector: 'app-workshop-details',
    styleUrls: ['./workshop-details.component.css'],
    templateUrl: './workshop-details.component.html'
})
export class WorkshopDetailsComponent implements OnInit {
    comments: CommentInfo[] = [];
    signupStatus: string = '';
    workshop?: WorkshopInfo;
    participatedBefore: boolean = false;
    mapUrl: string = 'https://tile.openstreetmap.org/level/tileX/tileY.png';
    signupButtonText: string = '';
    mapCenter?: {latitude: number, longitude: number};
    mapMarker = [{
        dataSource: [
            {
                latitude: 0,
                longitude: 0,
                name: ''
            }
        ],
        height: 50,
        visible: true,
        width: 50
    }];
    mapZoom = {
        enable: true,
        toolbars: ['Zoom', 'ZoomIn', 'ZoomOut', 'Pan', 'Reset'],
        zoomFactor: 17
    };
    id: number = 0;
    commentText: string = '';
    liked: boolean = false;
    /**
     * Injects the API service and Angular Router.
     * @param api API service to inject
     * @param router Angular Router to inject
     * @param util Utilities service to inject
     * @param route Current route information to inject
     */
    constructor(
        private api: ApiService,
        private router: Router,
        public util: UtilService,
        private route: ActivatedRoute
    ) {}
    /**
     * Required component initialization method.
     */
    async ngOnInit(): Promise<void> {
        if (!this.util.isLoggedIn()) {
            await this.util.redirectToLogin();
            return;
        }
        this.id = Number(
            this.route.snapshot.paramMap.get('id') ||
            '0'
        );
        const {
            comments,
            liked,
            participatedBefore,
            signupStatus,
            workshop
        } = await this.api.getWorkshop(this.id);
        this.participatedBefore = participatedBefore;
        this.liked = liked;
        this.comments = comments;
        this.signupStatus = signupStatus;
        this.workshop = workshop;
        this.mapCenter = {
            latitude: Number(workshop.latitude),
            longitude: Number(workshop.longitude)
        };
        this.mapMarker[0].dataSource[0] = {
            ...this.mapCenter,
            name: String(workshop.name)
        };
        this.signupButtonText = this.getSignupButtonText();
    }
    /**
     * Retrieves the sign up button text.
     * @returns Sign up button text
     */
    getSignupButtonText() {
        const now = new Date();
        const over12H = this.workshop &&
            new Date(this.workshop.date).getTime() -
            now.getTime() > 1000 * 60 * 60 * 12;
        return this.util.isOrganization() ?
            '' :
            this.signupStatus === 'can-cancel' ?
                over12H ?
                    'Cancel' :
                    '' :
                this.signupStatus === 'can-queue' ?
                    'Notify me when there are free places' :
                    'Sign up';
    }
    /**
     * Handles user signup.
     */
    async signup() {
        if (this.signupStatus === 'can-cancel') {
            await this.api.cancelSignup(this.id);
        } else {
            await this.api.signUp(this.id);
        }
        const {signupStatus} = await this.api.getWorkshop(this.id);
        this.signupStatus = signupStatus;
        this.signupButtonText = this.getSignupButtonText();
    }
    /**
     * Handles comment submission.
     * @param event DOM event arguments
     */
    async addComment(event: SubmitEvent) {
        event.preventDefault();
        const {comment} = await this.api.addComment(this.id, this.commentText);
        this.comments?.push(comment);
        if (this.workshop) {
            ++this.workshop.numComments;
        }
    }
    /**
     * Likes or dislikes the workshop.
     * @param event DOM event arguments
     */
    async updateLike(event: Event) {
        event.preventDefault();
        if (this.liked) {
            await this.api.removeLike(this.id);
            if (this.workshop) {
                --this.workshop.numLikes;
            }
        } else {
            await this.api.addLike(this.id);
            if (this.workshop) {
                ++this.workshop.numLikes;
            }
        }
        this.liked = !this.liked;
    }
    /**
     * Handles starting a new thread.
     */
    async startThread() {
        const {thread} = await this.api.startThread(this.id);
        await this.router.navigate(['/me'], {
            fragment: String(thread.id)
        });
    }
}
