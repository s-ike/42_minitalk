#include "minitalk.h"

int	ft_atoi(const char *str)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		num = (num * 10) + (*str++ - '0');
		if (num >> 63)
		{
			if (sign == -1)
				return ((int)(-__LONG_MAX__ - 1));
			return ((int)(__LONG_MAX__));
		}
	}
	return (num * sign);
}

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p)
		p++;
	return (p - s);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n < 10)
		write(fd, &("0123456789"[n]), 1);
	else if (10 <= n)
	{
		ft_putnbr_fd(n / 10, fd);
		write(fd, &("0123456789"[n % 10]), 1);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		write(fd, "\n", 1);
	}
}
