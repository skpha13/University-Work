using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace Lab3_23.Models.Base
{
    public class BaseEntity : IBaseEntity
    {
        [Key]
        // Generates a value when a row is inserted
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        //// Generates a value when a row in inserted or update
        //[DatabaseGenerated(DatabaseGeneratedOption.Computed)]
        //// does not update
        //[DatabaseGenerated(DatabaseGeneratedOption.None)]

        public Guid Id { get; set ; }
        public DateTime? DateTime { get; set; }
        public DateTime? LastModified { get; set; }
    }
}
