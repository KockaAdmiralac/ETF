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
import {IndexComponent} from './index/index.component';
import {LoginComponent} from './login/login.component';
import {NgModule} from '@angular/core';
import {ProfileComponent} from './profile/profile.component';
import {RegisterComponent} from './register/register.component';
import {
    ResetPasswordComponent
} from './reset-password/reset-password.component';
import {RouterModule} from '@angular/router';
import {UsersComponent} from './users/users.component';
import {
    WorkshopDetailsComponent
} from './workshop-details/workshop-details.component';
import {WorkshopsComponent} from './workshops/workshops.component';

/**
 * Module used for routing in the app.
 */
@NgModule({
    exports: [RouterModule],
    imports: [RouterModule.forRoot([
        {
            component: LoginComponent,
            path: 'account/login'
        },
        {
            component: RegisterComponent,
            path: 'account/register'
        },
        {
            component: ChangePasswordComponent,
            path: 'account/change-password'
        },
        {
            component: ForgotPasswordComponent,
            path: 'account/forgot-password'
        },
        {
            component: ResetPasswordComponent,
            path: 'account/forgot-password/:token'
        },
        {
            component: ProfileComponent,
            path: 'me'
        },
        {
            component: WorkshopsComponent,
            path: 'workshops'
        },
        {
            component: CreateWorkshopComponent,
            path: 'workshops/create'
        },
        {
            component: WorkshopDetailsComponent,
            path: 'workshops/:id'
        },
        {
            component: EditWorkshopComponent,
            path: 'workshops/:id/edit'
        },
        {
            component: UsersComponent,
            path: 'admin/users'
        },
        {
            component: IndexComponent,
            path: '**'
        }
    ])]
})
export class AppRoutingModule {}
