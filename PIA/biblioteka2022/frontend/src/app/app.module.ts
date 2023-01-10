import {AppComponent} from './app.component';
import {AppRoutingModule} from './app-routing.module';
import {BibliotekarComponent} from './bibliotekar/bibliotekar.component';
import {BrowserModule} from '@angular/platform-browser';
import {CitalacComponent} from './citalac/citalac.component';
import {FormsModule} from '@angular/forms';
import {HttpClientModule} from '@angular/common/http';
import {LoginComponent} from './login/login.component';
import {NgModule} from '@angular/core';

/**
 * Main application module.
 */
@NgModule({
    bootstrap: [AppComponent],
    declarations: [
        AppComponent,
        LoginComponent,
        CitalacComponent,
        BibliotekarComponent
    ],
    imports: [
        BrowserModule,
        AppRoutingModule,
        FormsModule,
        HttpClientModule
    ],
    providers: []
})
export class AppModule { }
