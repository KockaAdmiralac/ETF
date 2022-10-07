import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

export interface Extra {
  _id: string;
  name: string;
  amount: number;
}

export interface Order {
  _id: string;
  user: string;
  size: string;
  status: string;
  extras: string[];
}

export interface User {
  firstName: string;
  lastName: string;
}

@Injectable({
  providedIn: 'root'
})
export class ApiService {

  constructor(private client: HttpClient) { }

  baseUrl = 'http://localhost:4000';

  async getAllExtras(): Promise<Extra[]> {
    const {extras} = await (this.client.get(`${this.baseUrl}/extras`).toPromise() as Promise<any>);
    return extras;
  }

  async updateExtra(id: string) {
    await this.client.patch(`${this.baseUrl}/extras`, {id}).toPromise();
  }

  async getOrders(user?: string): Promise<Order[]> {
    const url = `${this.baseUrl}/orders`;
    const urlWithParams = user ? `${url}?user=${encodeURIComponent(user)}` : url;
    const {orders} = await (this.client.get(urlWithParams).toPromise() as Promise<any>);
    return orders;
  }

  async placeOrder(user: string, size: string, extras: string[]) {
    await this.client.post(`${this.baseUrl}/orders`, {
      extras,
      size,
      user
    }).toPromise();
  }

  async updateOrder(id: string, status: string) {
    await this.client.patch(`${this.baseUrl}/orders`, {
      id,
      status
    }).toPromise();
  }

  async login(username: string, password: string, type: string): Promise<User> {
    return this.client.post(`${this.baseUrl}/users/login`, {
      password,
      type,
      username
    }).toPromise() as Promise<User>;
  }
}
