import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ApiService } from '../api.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {

  constructor(private api: ApiService, private router: Router) { }

  username: string = '';
  password: string = '';
  type: string = '';
  error: string = '';

  ngOnInit(): void {
  }

  async submit() {
    this.error = '';
    if (!this.username || !this.password || !this.type) {
      this.error = 'All fields are required.';
      return;
    }
    try {
      const user = await this.api.login(this.username, this.password, this.type);
      sessionStorage.setItem('username', this.username);
      sessionStorage.setItem('firstName', user.firstName);
      sessionStorage.setItem('lastName', user.lastName);
      this.router.navigate([`/${this.type}`]);
    } catch (error) {
      this.error = error.error.message;
    }
  }

}
