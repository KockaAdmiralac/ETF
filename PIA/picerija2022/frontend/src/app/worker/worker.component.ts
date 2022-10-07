import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { ApiService, Extra, Order } from '../api.service';

@Component({
  selector: 'app-worker',
  templateUrl: './worker.component.html',
  styleUrls: ['./worker.component.css']
})
export class WorkerComponent implements OnInit {

  orders: Order[] = [];
  extras: Extra[] = [];

  constructor(private api: ApiService, private router: Router) { }

  async ngOnInit(): Promise<void> {
    this.orders = await this.api.getOrders();
    this.extras = await this.api.getAllExtras();
  }

  async update(order: Order, status: string) {
    await this.api.updateOrder(order._id, status);
    window.location.reload();
  }

  async order(extra: Extra) {
    await this.api.updateExtra(extra._id);
    extra.amount += 5;
  }

  logout() {
    sessionStorage.removeItem('username');
    this.router.navigate(['/']);
  }
}
