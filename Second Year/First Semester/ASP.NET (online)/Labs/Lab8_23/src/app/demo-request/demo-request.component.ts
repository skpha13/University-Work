import {Component, OnInit} from '@angular/core';
import {CommonModule, formatDate} from '@angular/common';
import {Student} from "../data/interfaces/student";
import {MatCardModule} from "@angular/material/card";
import {HttpClient, HttpClientModule, HttpHeaders} from "@angular/common/http";

@Component({
  selector: 'app-demo-request',
  standalone: true,
  imports: [CommonModule, MatCardModule, HttpClientModule],
  templateUrl: './demo-request.component.html',
  styleUrl: './demo-request.component.scss'
})
export class DemoRequestComponent implements OnInit {
  public StudentFromApi1: Student = {name: "", age: 0, id: 0}
  public StudentFromApi2: Student = {name: "", age: 0, id: 0}
  public StudentFromApi3: Student = {name: "", age: 0, id: 0}
  public StudentFromApi4: Student = {name: "", age: 0, id: 0}

  public Students: Student[] = []

  private readonly apiUrl = "https://localhost:7107/api";

  constructor(private readonly httpClient: HttpClient) {
  }

  ngOnInit(): void {
    let userId = 2;
    this.httpClient.get<Student>(`${this.apiUrl}/students/byId/${userId}`).subscribe(
      (data: Student) => {
        console.log(data);
        this.StudentFromApi1 = data;
      }
    );

    let params = {id: 3};
    this.httpClient.get<Student>(`${this.apiUrl}/students/fromQuery/`, {params}).subscribe(
      (data: Student) => {
        console.log(data);
        this.StudentFromApi2 = data;
      }
    );

    const headers = new HttpHeaders({
      'Content-Type': 'application/json',
      'id': '4'
    });
    this.httpClient.get<Student>(`${this.apiUrl}/students/fromHeader`, {headers}).subscribe(
      (data: Student) => {
        console.log(data);
        this.StudentFromApi3 = data;
      }
    );

    // form data
    const formData = new FormData();
    formData.append('name', 'Bob');
    formData.append('id', '6');
    formData.append('age', '40');
    this.httpClient.post(`${this.apiUrl}/students/fromForm`, formData).subscribe(
      (data) => {
        console.log(data);
      }
    );

    //body
    let newStudent = {
      Name: "Florin",
      Age: 24,
      Id: 7
    }
    this.httpClient.post(`${this.apiUrl}/students/fromBody`, newStudent).subscribe(
      (data) => {
        console.log(data);
      }
    );

    // patch
    let patchObject = [{
      'op': 'replace',
      'path': 'name',
      'value': 'Maria 1'
    }];

    let userId2 = 2;
    this.httpClient.patch(`${this.apiUrl}/students/${userId2}`, patchObject).subscribe(
      (data) => {
        console.log(data);
      }
    );
  }
}
