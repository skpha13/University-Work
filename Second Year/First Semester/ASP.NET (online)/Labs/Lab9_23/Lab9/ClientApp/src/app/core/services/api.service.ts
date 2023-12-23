import { Inject, Injectable } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {Observable} from "rxjs";

@Injectable({
  providedIn: 'root'
})
export class ApiService {
  //private readonly apiUrl = "https://localhost:7107/api";
  private readonly apiUrl: string;

  constructor(private readonly httpClient: HttpClient, @Inject('BASE_URL') apiUrl: string) {
    this.apiUrl = apiUrl;// + 'api/';
  }

  get<T>(path: string, params = {}): Observable<any>{
    return this.httpClient.get<T>(`${this.apiUrl}${path}`, {params});
  }

  put<T>(path: string, body = {}): Observable<any>{
    return this.httpClient.put<T>(`${this.apiUrl}${path}`, body);
  }

  post<T>(path: string, body = {}): Observable<any>{
    return this.httpClient.post<T>(`${this.apiUrl}${path}`, body);
  }

  delete<T>(path: string): Observable<any>{
    return this.httpClient.delete<T>(`${this.apiUrl}${path}`);
  }
}
