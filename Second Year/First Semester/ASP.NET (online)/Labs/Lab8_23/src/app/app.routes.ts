import {Routes} from '@angular/router';
import {Route1Component} from "./routing/route1/route1.component";
import {Route2Component} from "./routing/route2/route2.component";
import {RegisterComponent} from "./reactive-forms/register/register.component";
import {DemoRequestComponent} from "./demo-request/demo-request.component";

export const routes: Routes = [{
  path: 'route1-component',
  component: Route1Component
},
  {
    path: 'route2-component',
    component: Route2Component
  }, {
    path: 'register',
    component: RegisterComponent
  }, {
    path: 'requests',
    component: DemoRequestComponent
  }];
