import {Component, OnChanges, OnDestroy, OnInit, SimpleChanges} from '@angular/core';
import {CommonModule} from '@angular/common';
import {MatCardModule} from '@angular/material/card';
import {MatIconModule} from '@angular/material/icon';
import {MatDividerModule} from '@angular/material/divider';
import {MatButtonModule} from '@angular/material/button';
import {MatListModule} from '@angular/material/list';
import {MatInputModule} from "@angular/material/input";
import {FormsModule} from "@angular/forms";

@Component({
  selector: 'app-demo',
  standalone: true,
  imports: [CommonModule, MatCardModule, MatButtonModule, MatDividerModule, MatIconModule, MatListModule, MatInputModule, FormsModule],
  templateUrl: './demo.component.html',
  styleUrl: './demo.component.scss'
})
//, DoCheck, AfterContentChecked
export class DemoComponent implements OnInit, OnDestroy, OnChanges {
  public title: string = "Demo Component";
  public counter: number = 0;
  public selectedUser: any = {};

  public users = [
    {id: 1, name: 'Name 1', background: 'lightgreen'},
    {id: 2, name: 'Name 2', background: 'blue'},
    {id: 3, name: 'Name 3', background: 'purple'},
    {id: 4, name: 'Name 4', background: 'orange'}
  ];

  constructor() {
    let div = document.getElementById('titleContainer');
    console.log("Constructor titleContainer value", div);
  }

  addToCounter() {
    this.counter++;
  }

  selectUser(user: any) {
    this.selectedUser = user;
  }

  deleteUser() {
    this.users.pop();
  }

  addUser() {
    let length = this.users.length + 1
    this.users.push({id: length, name: 'Name ' + length, background: "gray"})
  }

  ngOnChanges(changes: SimpleChanges): void {
  }

  ngOnDestroy(): void {
  }

  ngOnInit(): void {
    let div = document.getElementById('titleContainer');
    console.log("OnInit titleContainer value", div);
  }


}
