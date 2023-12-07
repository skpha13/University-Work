import {Component} from '@angular/core';
import {CommonModule} from '@angular/common';
import {DemoPipe} from "../../core/pipes/demo.pipe";
import {MouseEnterDirective} from "../../core/directives/mouse-enter.directive";
import {ImagePreloaderDirective} from "../../core/directives/image-preloader.directive";

@Component({
  selector: 'app-route1',
  standalone: true,
  imports: [CommonModule, DemoPipe, MouseEnterDirective, ImagePreloaderDirective],
  templateUrl: './route1.component.html',
  styleUrl: './route1.component.scss'
})
export class Route1Component {
  valueForPipe1 = '1';
  valueForPipe2 = '23';
  imageUrl = 'https://buffer.com/library/content/images/2023/09/instagram-image-size.jpg'
  // imageUrl = 'https://thescranline.com/wp-content/uploads/2021/03/Vanilla-Cupcakes';
}
