import {ApiService, WorkshopInfo} from '../api.service';
import {Component, OnInit} from '@angular/core';
import {Router} from '@angular/router';
import {UtilService} from '../util.service';

/**
 * Component for the workshop listing screen.
 */
@Component({
    selector: 'app-workshops',
    styleUrls: ['./workshops.component.css'],
    templateUrl: './workshops.component.html'
})
export class WorkshopsComponent implements OnInit {
    searchName: string = '';
    searchPlace: string = '';
    workshops: WorkshopInfo[] = [];
    shownWorkshops: WorkshopInfo[] = [];
    top5Workshops: WorkshopInfo[] = [];
    myWorkshops: WorkshopInfo[] = [];
    error: string = '';
    /**
     * Injects the API service and Angular Router.
     * @param api API service to inject
     * @param router Angular Router to inject
     * @param util Utilities service to inject
     */
    constructor(
        private api: ApiService,
        private router: Router,
        public util: UtilService
    ) { }
    /**
     * Required component initialization method.
     */
    async ngOnInit(): Promise<void> {
        const {signups, workshops} = await this.api.getAllWorkshops();
        this.workshops = workshops;
        if (!this.util.isAdmin()) {
            const today = new Date();
            this.workshops = this.workshops.filter(
                w => w.user.id === this.util.getUserId() ||
                     w.active && new Date(w.date) > today
            );
        }
        if (this.util.isOrganization()) {
            this.myWorkshops = this.workshops
                .filter(w => w.user.id === this.util.getUserId());
        } else {
            const today = new Date();
            this.myWorkshops = signups
                .map((id: number) => this.workshops.find(w => w.id === id))
                .filter(Boolean)
                .filter((w: WorkshopInfo) => new Date(w.date) > today);
        }
        this.shownWorkshops = this.workshops;
        this.top5Workshops = this.workshops
            .sort((w1, w2) => w1.numLikes - w2.numLikes)
            .slice(0, 5);
    }
    /**
     * Sorts workshops by the specified property.
     * @param property Property to sort by
     */
    sortBy(property: 'name' | 'date' | 'place' | 'snippet') {
        this.shownWorkshops = this.workshops
            .sort((w1, w2) => w1[property]
                .toString()
                .localeCompare(w2[property].toString()));
    }
    /**
     * Updates rows shown when search queries are changed.
     */
    updateSearch() {
        this.shownWorkshops = this.workshops
            .filter(
                w => w.name.includes(this.searchName) &&
                     w.place.includes(this.searchPlace)
        );
    }
    /**
     * Handles workshop deletion.
     * @param id ID of the workshop to delete
     */
    async deleteWorkshop(id: number) {
        try {
            await this.api.deleteWorkshop(id);
            this.workshops = this.workshops.filter(w => w.id !== id);
            this.shownWorkshops = this.workshops.filter(w => w.id !== id);
            this.myWorkshops = this.workshops.filter(w => w.id !== id);
        } catch (error: any) {
            this.error = error.error.error;
        }
    }
    /**
     * Approves a workshop.
     * @param id ID of the workshop to approve
     */
    async approveWorkshop(id: number) {
        try {
            await this.api.editWorkshop(id, {
                active: true
            });
            const workshop = this.workshops.find(w => w.id === id);
            if (workshop) {
                workshop.active = true;
            }
            const myWorkshop = this.myWorkshops.find(w => w.id === id);
            if (myWorkshop) {
                myWorkshop.active = true;
            }
        } catch (error: any) {
            this.error = error.error.error;
        }
    }
}
