# Lab 11

## 1

- a - T
- b - F
- c - T
- d - T
- e - F
- f - F
- g - F
- h - T
- i - F

## 2

```csharp
[AllowAnonymous]
[ProducesResponseType(typeof(ErrorResponse), 200)]
[ProducesResponseType(typeof(ErrorResponse), 500)]
[HttpPost("register")]
public async Task<IActionResult> SignUp([FromBody] SignUpDTO signUpDto)
{
    try
    {
        return Ok(await _userService.SignUp(signUpDto));
    }
    catch (AccountAlreadyExistsException exception)
    {
        return BadRequest(new ErrorResponse()
        {
            StatusCode = 400,
            Message = exception.Message
        });
    }
    catch (Exception exception)
    {
        return BadRequest(new ErrorResponse()
        {
            StatusCode = 500,
            Message = exception.Message
        });
    }
}
```

> Checks to see if an account with this email already exists.

```csharp
builder.Services.Configure<IdentityOptions>(opt =>
{
	opt.Password.RequireDigit = true;
	opt.Password.RequiredLength = 8;
	opt.User.RequireUniqueEmail = true;
	opt.SignIn.RequireConfirmedAccount = false;
	opt.SignIn.RequireConfirmedEmail = false;
	opt.SignIn.RequireConfirmedPhoneNumber = false;
	opt.SignIn.RequireConfirmedEmail = false;
	opt.Lockout.AllowedForNewUsers = false;
});
```

> Configuration settings for email and password.

```typescript
<PageTitle title="Sign Up" />
<FormKit type="form" @submit="registerHandler" submit-label="Sign Up">
<FormKit type="text"
            name="username"
            label="Username"
            placeholder="client"
            validation="required"
            validation-visibility="live" />

<FormKit type="email"
            name="email"
            label="Email"
            placeholder="client@gmail.com"
            validation="email|required"
            validation-visibility="live" />

    <FormKit type="password"
            name="password"
            label="Password"
            placeholder="password"
            prefix-icon="password"
            suffix-icon="eyeClosed"
            @suffix-icon-click="handleIconClick"
            validation="required|length:8"
            validation-visibility="live" />

    <FormKit type="password"
            name="password_confirm"
            label="Confirm password"
            validation="required|confirm"
            validation-visibility="live"
            validation-label="Confirmation" />
</FormKit>
```

> Valid email check, password confirmation, password visibilty disabled.

## 3

```csharp
[AllowAnonymous]
[HttpPost("login")]
[ProducesResponseType(typeof(ResponseLoginDTO), 200)]
[ProducesResponseType(typeof(ErrorResponse), 500)]
public async Task<IActionResult> Login([FromBody] LoginDTO loginBody)
{
    try
    {
        return Ok(new ResponseLoginDTO()
        {
            Id =  await _userService.Login(loginBody)
        });
    }
    catch (EmailNotFoundException exception)
    {
        return NotFound(new ErrorResponse()
        {
            StatusCode = 404,
            Message = exception.Message
        });
    }
    catch (Exception exception)
    {
        return BadRequest(new ErrorResponse()
        {
            StatusCode = 500,
            Message = exception.Message
        });
    }
}
```

> Checks if account exists based on email.

```typescript
<PageTitle title="Login" />
<FormKit type="form" @submit="loginHandler" submit-label="Login">
<FormKit
    type="email"
    name="email"
    label="Email"
    placeholder="client@gmail.com"
    validation="email|required"
    validation-visibility="live"
/>

<FormKit
    type="password"
    name="password"
    label="Password"
    placeholder="password"
    validation="required|length:8"
    prefix-icon="password"
    suffix-icon="eyeClosed"
    @suffix-icon-click="handleIconClick"
    validation-visibility="live"
/>
```

> Email validation and password conditions checked.

```csharp
builder.Services.AddCors(options =>
{
	options.AddPolicy(name: MyAllowSpecificOrigins, policy =>
	{
		policy.WithOrigins("http://localhost:5173", "https://localhost:5173")
			.AllowAnyHeader()
			.AllowAnyMethod()
			.AllowCredentials();
	});
});
```

> Protection agains CSRF (Cross-Site Request Forgery)

```csharp
using Microsoft.EntityFrameworkCore;

namespace backend.Repositories.GenericRepository;

public class GenericRepository<TEntity> : IGenericRepository<TEntity> where TEntity : BaseEntity
{
    protected readonly DatabaseContext _dbContext;
    protected readonly DbSet<TEntity> _table;
}
```

> Entity Framework used for ORM, protects agains SQL injections and XSS (Cross-Site Scripting)