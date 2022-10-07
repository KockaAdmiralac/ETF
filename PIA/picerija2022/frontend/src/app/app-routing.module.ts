import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { LoginComponent } from './login/login.component';
import { UserComponent } from './user/user.component';
import { WorkerComponent } from './worker/worker.component';

const routes: Routes = [
  {
    path: '',
    component: LoginComponent
  },
  {
    path: 'kupac',
    component: UserComponent
  },
  {
    path: 'radnik',
    component: WorkerComponent
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
