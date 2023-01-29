import {
    AnnotationsService,
    BubbleService,
    DataLabelService,
    LegendService,
    MapsModule,
    MapsTooltipService,
    MarkerService,
    NavigationLineService,
    SelectionService,
    ZoomService
} from '@syncfusion/ej2-angular-maps';
import {AppComponent} from './app.component';
import {AppRoutingModule} from './app-routing.module';
import {BrowserModule} from '@angular/platform-browser';
import {
    ChangePasswordComponent
} from './change-password/change-password.component';
import {
    CreateWorkshopComponent
} from './create-workshop/create-workshop.component';
import {EditWorkshopComponent} from './edit-workshop/edit-workshop.component';
import {
    ForgotPasswordComponent
} from './forgot-password/forgot-password.component';
import {FormsModule} from '@angular/forms';
import {HttpClientModule} from '@angular/common/http';
import {IndexComponent} from './index/index.component';
import {LoginComponent} from './login/login.component';
import {NgModule} from '@angular/core';
import {ProfileComponent} from './profile/profile.component';
import {RegisterComponent} from './register/register.component';
import {
    ResetPasswordComponent
} from './reset-password/reset-password.component';
import {UsersComponent} from './users/users.component';
import {
    WorkshopDetailsComponent
} from './workshop-details/workshop-details.component';
import {WorkshopsComponent} from './workshops/workshops.component';

/**
 * Main app module.
 */
@NgModule({
    bootstrap: [AppComponent],
    declarations: [
        AppComponent,
        LoginComponent,
        ChangePasswordComponent,
        ForgotPasswordComponent,
        ResetPasswordComponent,
        RegisterComponent,
        WorkshopsComponent,
        ProfileComponent,
        WorkshopDetailsComponent,
        EditWorkshopComponent,
        CreateWorkshopComponent,
        UsersComponent,
        IndexComponent
    ],
    imports: [
        BrowserModule,
        AppRoutingModule,
        FormsModule,
        HttpClientModule,
        MapsModule
    ],
    providers: [
        LegendService,
        MarkerService,
        MapsTooltipService,
        DataLabelService,
        BubbleService,
        NavigationLineService,
        SelectionService,
        AnnotationsService,
        ZoomService
    ]
})
export class AppModule { }
