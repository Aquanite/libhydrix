#include <libhydrix/htime/htime.h>
#include <libhydrix/hio/io.h>

long long TimeAtBoot = 0;

int readPit(void)
{
	unsigned count = 0;
	asm volatile("cli");
	outb(0x43, 0b0000000);
	count = inb(0x40);
	count |= inb(0x40) << 8;
	asm volatile("sti");
	return count;
}

void setPit(unsigned count)
{
	asm volatile("cli");
	outb(0x40, count & 0xFF);					 // Low byte
	outb(0x40, (count & 0xFF00) >> 8); // High byte
	asm volatile("sti");
	return;
}

int getSeconds()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	outb(cmos_address, 0x0);
	int second = inb(cmos_data);
	second = (second & 0x0F) + ((second / 16) * 10);
	return second;
}

int getMinutes()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	outb(cmos_address, 0x02);
	int minute = inb(cmos_data);
	minute = (minute & 0x0F) + ((minute / 16) * 10);
	return minute;
}

int getHours()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	outb(cmos_address, 0x04);
	int hour = inb(cmos_data);
	hour = (hour & 0x0F) + ((hour / 16) * 10);
	return hour;
}

void time_init()
{
	TimeAtBoot = (getSeconds() + (getMinutes() * 60) + (getHours() * 3600));
}

long long currentTime()
{
	return (getSeconds() + (getMinutes() * 60) + (getHours() * 3600));
}

int getCentury()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	outb(cmos_address, 0x32);
	int century = inb(cmos_data);
	century = (century & 0x0F) + ((century / 16) * 10);
	return century;
}

int getYear()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	outb(cmos_address, 0x09);
	int year = inb(cmos_data);
	year = (year & 0x0F) + ((year / 16) * 10);
	return year;
}

int getMonth()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	outb(cmos_address, 0x08);
	int month = inb(cmos_data);
	month = (month & 0x0F) + ((month / 16) * 10);
	return month;
}

int getDay()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	outb(cmos_address, 0x07);
	int day = inb(cmos_data);
	day = (day & 0x0F) + ((day / 16) * 10);
	return day;
}

int getDayOfWeek()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	outb(cmos_address, 0x06);
	int day = inb(cmos_data);
	return day;
}

long long getTimeFromBoot()
{
    // Returns the time from boot in seconds
	return (getSeconds() + (getMinutes() * 60) + (getHours() * 3600)) - TimeAtBoot;
}

TIMEZONE_OFFSET CurrentSelectedTimezone = UTC;

void SetCurrentTimezone(TIMEZONE_OFFSET offset)
{
	CurrentSelectedTimezone = offset;
}

TIMEZONE_OFFSET GetCurrentTimezone()
{
	return CurrentSelectedTimezone;
}
Time_t getTime(TIMEZONE_OFFSET timezone)
{
	Time_t time;
	time.seconds = getSeconds();
	time.minutes = getMinutes();
	time.hours = getHours();

	// Add timezone offset
	time.hours += timezone;

	// If the timezone is India (Mumbai), add 30 minutes
	if (timezone == Mumbai)
	{
		time.minutes += 30;
		if (time.minutes >= 60)
		{
			time.minutes -= 60;
			time.hours++;
		}
	}

	// Wrap around the hours if negative or greater than 23
	if (time.hours < 0)
	{
		time.hours += 24;
	}
	else if (time.hours >= 24)
	{
		time.hours -= 24;
	}

	time.pm = false;
	return time;

}
Time_t getTime()
{
	Time_t time;
	time.seconds = getSeconds();
	time.minutes = getMinutes();
	time.hours = getHours();

	// Add timezone offset
	time.hours += CurrentSelectedTimezone;

	// If the timezone is India (Mumbai), add 30 minutes
	if (CurrentSelectedTimezone == Mumbai)
	{
		time.minutes += 30;
		if (time.minutes >= 60)
		{
			time.minutes -= 60;
			time.hours++;
		}
	}

	// Wrap around the hours if negative or greater than 23
	if (time.hours < 0)
	{
		time.hours += 24;
	}
	else if (time.hours >= 24)
	{
		time.hours -= 24;
	}

	time.pm = false;
	return time;
}

Time_t convertTo12Hour(Time_t time)
{
	if (time.hours == 0)
	{
		time.hours = 12;
		time.pm = false;
	}
	else if (time.hours == 12)
	{
		time.pm = true;
	}
	else if (time.hours > 12)
	{
		time.hours -= 12;
		time.pm = true;
	}
	else
	{
		time.pm = false;
	}
	return time;
}

Time_t getTime12Hour(TIMEZONE_OFFSET SpecifiedTimezone)
{
	Time_t time;
	time.seconds = getSeconds();
	time.minutes = getMinutes();
	time.hours = getHours();

	// Add timezone offset
	time.hours += SpecifiedTimezone;

	// If the timezone is India (Mumbai), add 30 minutes
	if (SpecifiedTimezone == Mumbai)
	{
		time.minutes += 30;
		if (time.minutes >= 60)
		{
			time.minutes -= 60;
			time.hours++;
		}
	}

	// Wrap around the hours if negative or greater than 23
	if (time.hours < 0)
	{
		time.hours += 24;
	}
	else if (time.hours >= 24)
	{
		time.hours -= 24;
	}

	// Convert to 12-hour format
	time = convertTo12Hour(time);

	return time;
}

Time_t getTime12Hour()
{
	Time_t time = getTime();
	// Convert to 12-hour format
	return convertTo12Hour(time);
}
