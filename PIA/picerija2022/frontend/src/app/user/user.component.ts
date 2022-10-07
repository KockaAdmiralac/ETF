import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ApiService, Extra, Order } from '../api.service';

@Component({
  selector: 'app-user',
  templateUrl: './user.component.html',
  styleUrls: ['./user.component.css']
})
export class UserComponent implements OnInit {

  user: string = '';
  firstName: string = '';
  lastName: string = '';
  orders: Order[] = [];
  extras: Extra[] = [];
  size: string = '';
  selectedExtras = new Set<string>();

  constructor(private api: ApiService, private router: Router) { }

  async ngOnInit(): Promise<void> {
    this.user = sessionStorage.getItem('username') || '';
    this.firstName = sessionStorage.getItem('firstName') || '';
    this.lastName = sessionStorage.getItem('lastName') || '';
    this.orders = await this.api.getOrders(this.user);
    this.extras = await this.api.getAllExtras();
  }

  changeExtra(extra: Extra) {
    if (this.selectedExtras.has(extra.name)) {
      this.selectedExtras.delete(extra.name);
    } else {
      this.selectedExtras.add(extra.name);
    }
  }

  async submit() {
    await this.api.placeOrder(this.user, this.size, [...this.selectedExtras]);
    window.location.reload();
  }

  logout() {
    sessionStorage.removeItem('username');
    this.router.navigate(['/']);
  }
}
