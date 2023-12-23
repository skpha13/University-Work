import {Directive, Input, OnInit} from '@angular/core';

@Directive({
  selector: '[appImagePreloader]',
  standalone: true,
  host: {
    '[attr.src]': 'finalImage'
  }
})
export class ImagePreloaderDirective implements OnInit {
  @Input('appImagePreloader') targetSource: string = "";
  defaultImage: string = 'https://i.stack.imgur.com/MEBIB.gif';
  finalImage: any;
  downloadingImage: any;

  constructor() {
  }

  ngOnInit(): void {
    this.finalImage = this.defaultImage;
    this.downloadingImage = new Image();
    this.downloadingImage.src = this.targetSource;

    this.downloadingImage.onload = () => {
      this.finalImage = this.targetSource;
    }
    this.downloadingImage.onerror = (e: any) => console.error(e);
  }

}
