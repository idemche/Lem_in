#include "ft_printf/libftprintf.h"

int	main()
{
    ft_printf("%03.2d\n", 0);
    printf("%03.2d\n\n", 0);
    
    ft_printf("%03.2d\n", 1);
    printf("%03.2d\n\n", 1);
	return(0);
}
