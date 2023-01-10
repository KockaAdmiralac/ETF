import {BibliotekarComponent} from './bibliotekar/bibliotekar.component';
import {CitalacComponent} from './citalac/citalac.component';
import {LoginComponent} from './login/login.component';
import {NgModule} from '@angular/core';
import {RouterModule} from '@angular/router';

/**
 * Module for routing throughout the application.
 */
@NgModule({
    exports: [RouterModule],
    imports: [RouterModule.forRoot([
        {
            component: LoginComponent,
            path: ''
        },
        {
            component: CitalacComponent,
            path: 'citalac'
        },
        {
            component: BibliotekarComponent,
            path: 'bibliotekar'
        }
    ])]
})
export class AppRoutingModule { }
