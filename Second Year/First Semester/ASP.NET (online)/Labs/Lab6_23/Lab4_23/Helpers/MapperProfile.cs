using AutoMapper;
using Lab4_23.Models;
using Lab4_23.Models.DTOs;

namespace Lab4_23.Helpers
{
    public class MapperProfile: Profile
    {
        public MapperProfile() {

            CreateMap<User, UserDto>();
            CreateMap<UserDto, User>();

            CreateMap<User, UserDto>()
                .ForMember( ud => ud.FullName,
                opts => opts.MapFrom(u => u.FirstName + u.LastName));
        }
    }
}
