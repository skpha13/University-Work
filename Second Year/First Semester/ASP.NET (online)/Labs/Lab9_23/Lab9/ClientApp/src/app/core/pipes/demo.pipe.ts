import {Pipe, PipeTransform} from '@angular/core';

@Pipe({
  name: 'demo',
  standalone: true
})
export class DemoPipe implements PipeTransform {

  transform(value: string, ...args: unknown[]): unknown {
    switch (value[value.length - 1]) {
      case '1':
        return value + 'st';
      case '2':
        return value + 'nd';
      case '3':
        return value + 'rd';
      default:
        return value + 'th';
    }
  }

}
