import {Component} from '@angular/core';
import {CommonModule} from '@angular/common';
import {FormBuilder, FormControl, FormGroup, ReactiveFormsModule, Validators} from "@angular/forms";
import { AuthenticationService } from '../../core/services/authentication.service';

@Component({
  selector: 'app-register',
  standalone: true,
  imports: [CommonModule, ReactiveFormsModule],
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.scss']
})
export class RegisterComponent {
  registerForm = this.formBuilder.group({
    userName: ['', Validators.required],
    email: ['', Validators.email],
    password: ['', Validators.required],
    firstName: ['', Validators.required],
    lastName: ['', Validators.required],
  })

  registerForm2 = new FormGroup({
    username: new FormControl('', Validators.required),
    email: new FormControl('', Validators.email),
    password: new FormControl('')
  })

  constructor(private readonly formBuilder: FormBuilder, private readonly authenticationService: AuthenticationService) {

  }

  register() {
    console.log(this.registerForm.value);
    this.authenticationService.login(this.registerForm.value).subscribe(data => console.log(data));

  }

}
