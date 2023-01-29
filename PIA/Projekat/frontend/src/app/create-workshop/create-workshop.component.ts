import {Component, OnInit} from '@angular/core';
import {ApiService} from '../api.service';
import {Router} from '@angular/router';
import {UtilService} from '../util.service';

/**
 * Component for the workshop creation screen.
 */
@Component({
    selector: 'app-create-workshop',
    templateUrl: './create-workshop.component.html'
})
export class CreateWorkshopComponent implements OnInit {
    name: string = '';
    date: string = '';
    place: string = '';
    latitude: string = '';
    longitude: string = '';
    capacity: string = '';
    description: string = '';
    snippet: string = '';
    error: string = '';
    mainImage?: File;
    galleryImages: File[] = [];
    photos: number[] = [];
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
    ngOnInit(): void {
        if (!this.util.isLoggedIn()) {
            this.util.redirectToLogin();
        }
    }
    /**
     * Handles workshop creation form submission.
     * @param event Event arguments
     */
    async createWorkshop(event: SubmitEvent) {
        event.preventDefault();
        if (
            !this.capacity ||
            !this.date ||
            !this.description ||
            !this.latitude ||
            !this.longitude ||
            !this.name ||
            !this.place ||
            !this.snippet ||
            !(this.mainImage || this.photos.length > 0)
        ) {
            this.error = 'All fields except the last one are required.';
            return;
        }
        const photos = new FormData();
        if (this.mainImage) {
            photos.append('photos', this.mainImage);
        }
        this.galleryImages.forEach(f => photos.append('photos', f));
        try {
            const workshop = await this.api.createWorkshop({
                capacity: Number(this.capacity),
                date: new Date(this.date),
                description: this.description,
                latitude: Number(this.latitude),
                longitude: Number(this.longitude),
                name: this.name,
                photos: this.photos.length > 0 ? this.photos : photos,
                place: this.place,
                snippet: this.snippet
            });
            this.router.navigate(['/workshops', workshop.id]);
        } catch (error: any) {
            this.error = error.error.error;
        }
    }
    /**
     * Updates images to be uploaded with workshop creation.
     * @param event File upload field change event
     * @param type Type of image field to update
     */
    updateImages(event: Event, type: 'gallery' | 'main') {
        if (type === 'gallery') {
            this.galleryImages = [];
        } else {
            delete this.mainImage;
        }
        for (const file of (event?.currentTarget as any).files) {
            if (type === 'main') {
                this.mainImage = file;
            } else {
                this.galleryImages.push(file);
            }
        }
    }
    /**
     * Handles workshop template upload.
     * @param event DOM event arguments
     */
    importTemplate(event: Event) {
        const file = (event?.currentTarget as any).files.item(0);
        const reader = new FileReader();
        reader.addEventListener('load', function(
            this: CreateWorkshopComponent,
            readerEvent: ProgressEvent<FileReader>
        ) {
            const contents = readerEvent.target?.result;
            if (typeof contents !== 'string') {
                return;
            }
            const {
                name,
                date,
                place,
                latitude,
                longitude,
                capacity,
                description,
                snippet,
                photos
            } = JSON.parse(contents);
            this.name = name;
            this.date = date;
            this.place = place;
            this.latitude = latitude;
            this.longitude = longitude;
            this.capacity = capacity;
            this.description = description;
            this.snippet = snippet;
            this.photos = photos;
        }.bind(this));
        reader.readAsText(file);
    }
}
