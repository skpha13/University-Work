import {Component} from '@angular/core';
import {CommonModule} from '@angular/common';
import {FormBuilder, FormControl, FormGroup, ReactiveFormsModule, Validators} from "@angular/forms";

@Component({
  selector: 'app-register',
  standalone: true,
  imports: [CommonModule, ReactiveFormsModule],
  templateUrl: './register.component.html',
  styleUrl: './register.component.scss'
})
export class RegisterComponent {
  registerForm = this.formBuilder.group({
    userName: ['', Validators.required],
    email: ['', Validators.email],
    password: ['', Validators.required]
  })

  registerForm2 = new FormGroup({
    userName: new FormControl('', Validators.required),
    email: new FormControl('', Validators.email),
    password: new FormControl('')
  })

  constructor(private readonly formBuilder: FormBuilder) {

  }

  checkForm() {
    console.log(this.registerForm);

    console.log(this.registerForm.value);
  }

}
