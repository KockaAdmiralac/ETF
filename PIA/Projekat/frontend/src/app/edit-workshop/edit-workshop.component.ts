import {ActivatedRoute, Router} from '@angular/router';
import {ApiService, UserInfo} from '../api.service';
import {Component, OnInit} from '@angular/core';
import {UtilService} from '../util.service';

/**
 * Component for the workshop editing screen.
 */
@Component({
    selector: 'app-edit-workshop',
    templateUrl: './edit-workshop.component.html'
})
export class EditWorkshopComponent implements OnInit {
    id: number = 0;
    name: string = '';
    date: string = '';
    place: string = '';
    latitude: string = '';
    longitude: string = '';
    capacity: string = '';
    description: string = '';
    snippet: string = '';
    error: string = '';
    photos: number[] = [];
    signups: UserInfo[] = [];
    /**
     * Injects the API service and Angular Router.
     * @param api API service to inject
     * @param router Angular Router to inject
     * @param util Utilities service to inject
     * @param route Currently active route
     */
    constructor(
        private api: ApiService,
        private router: Router,
        public util: UtilService,
        private route: ActivatedRoute
    ) { }
    /**
     * Required component initialization method.
     */
    async ngOnInit(): Promise<void> {
        if (!this.util.isOrganization()) {
            await this.util.redirectToLogin();
            return;
        }
        this.id = Number(
            this.route.snapshot.paramMap.get('id') ||
            '0'
        );
        const {signups, workshop} = await this.api.getWorkshop(this.id);
        this.signups = signups;
        this.name = workshop.name;
        this.date = new Date(workshop.date).toISOString().slice(0, 16);
        this.place = workshop.place;
        this.latitude = workshop.latitude;
        this.longitude = workshop.longitude;
        this.capacity = workshop.capacity;
        this.description = workshop.description;
        this.snippet = workshop.snippet;
        this.photos = workshop.photos;
    }
    /**
     * Handles edit form submission.
     * @param event Event arguments
     */
    async editWorkshop(event: SubmitEvent) {
        event.preventDefault();
        await this.api.editWorkshop(this.id, {
            capacity: Number(this.capacity),
            date: this.date,
            description: this.description,
            latitude: Number(this.latitude),
            longitude: Number(this.longitude),
            name: this.name,
            place: this.place,
            snippet: this.snippet
        });
        await this.router.navigate([`/workshops/${this.id}`]);
    }
    /**
     * Handles additional image upload.
     * @param event Event arguments
     */
    async updateImages(event: Event) {
        event.preventDefault();
        const files = new FormData();
        for (const file of (event?.currentTarget as any).files) {
            files.append('photos', file);
        }
        const {photos} = await this.api.addGalleryImages(this.id, files);
        this.photos = photos;
    }
    /**
     * Handles signup accepting.
     * @param user Information about the user to accept
     */
    async acceptSignup(user: UserInfo) {
        await this.api.acceptSignup(this.id, user.id);
        this.signups = this.signups.filter(s => s.id !== user.id);
    }
    /**
     * Handles workshop cancellation.
     */
    async cancelWorkshop() {
        await this.api.editWorkshop(this.id, {
            active: false
        });
        await this.router.navigate(['/workshops']);
    }
    /**
     * Handles saving the workshop as a JSON template.
     */
    saveTemplate() {
        const templateData = {
            capacity: Number(this.capacity),
            date: this.date,
            description: this.description,
            latitude: Number(this.latitude),
            longitude: Number(this.longitude),
            name: this.name,
            photos: this.photos,
            place: this.place,
            snippet: this.snippet
        };
        const blob = new Blob([JSON.stringify(templateData)], {
            type: 'application/json'
        });
        const blobUrl = URL.createObjectURL(blob);
        const downloadLink = document.createElement('a');
        downloadLink.href = blobUrl;
        downloadLink.download = `workshop-template-${this.id}.json`;
        document.body.appendChild(downloadLink);
        downloadLink.click();
        URL.revokeObjectURL(blobUrl);
    }
}
