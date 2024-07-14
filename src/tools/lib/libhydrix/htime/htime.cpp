#include <libhydrix/htime/htime.h>
#include <libhydrix/hio/io.h>

long long TimeAtBoot = 0;

int readPit(void)
{
	unsigned count = 0;
	asm volatile("cli");
	PortIO::OutByte(0x43, 0b0000000);
	count = PortIO::InByte(0x40);
	count |= PortIO::InByte(0x40) << 8;
	asm volatile("sti");
	return count;
}

void setPit(unsigned count)
{
	asm volatile("cli");
	PortIO::OutByte(0x40, count & 0xFF);					 // Low byte
	PortIO::OutByte(0x40, (count & 0xFF00) >> 8); // High byte
	asm volatile("sti");
	return;
}

int TimeGetSeconds()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	PortIO::OutByte(cmos_address, 0x0);
	int second = PortIO::InByte(cmos_data);
	second = (second & 0x0F) + ((second / 16) * 10);
	return second;
}

int TimeGetMinutes()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	PortIO::OutByte(cmos_address, 0x02);
	int Minimumute = PortIO::InByte(cmos_data);
	Minimumute = (Minimumute & 0x0F) + ((Minimumute / 16) * 10);
	return Minimumute;
}

int TimeGetHours()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	PortIO::OutByte(cmos_address, 0x04);
	int hour = PortIO::InByte(cmos_data);
	hour = (hour & 0x0F) + ((hour / 16) * 10);
	return hour;
}

void InitializeTime()
{
	TimeAtBoot = (TimeGetSeconds() + (TimeGetMinutes() * 60) + (TimeGetHours() * 3600));
}

long long TimeCurrentTime()
{
	return (TimeGetSeconds() + (TimeGetMinutes() * 60) + (TimeGetHours() * 3600));
}

int TimeGetCentury()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	PortIO::OutByte(cmos_address, 0x32);
	int century = PortIO::InByte(cmos_data);
	century = (century & 0x0F) + ((century / 16) * 10);
	return century;
}

int TimeGetYear()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	PortIO::OutByte(cmos_address, 0x09);
	int year = PortIO::InByte(cmos_data);
	year = (year & 0x0F) + ((year / 16) * 10);
	return year;
}

int TimeGetMonth()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	PortIO::OutByte(cmos_address, 0x08);
	int month = PortIO::InByte(cmos_data);
	month = (month & 0x0F) + ((month / 16) * 10);
	return month;
}

int TimeGetDay()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	PortIO::OutByte(cmos_address, 0x07);
	int day = PortIO::InByte(cmos_data);
	day = (day & 0x0F) + ((day / 16) * 10);
	return day;
}

int TimeGetDayOfTheWeek()
{
	int cmos_address = 0x70;
	int cmos_data = 0x71;
	PortIO::OutByte(cmos_address, 0x06);
	int day = PortIO::InByte(cmos_data);
	return day;
}

long long TimeSinceBootMS()
{
    // Returns the time from boot in seconds
	return (TimeGetSeconds() + (TimeGetMinutes() * 60) + (TimeGetHours() * 3600)) - TimeAtBoot;
}

TimezoneOffset_t CurrentSelectedTimezone = UTC;

void SetCurrentTimezone(TimezoneOffset_t offset)
{
	CurrentSelectedTimezone = offset;
}

TimezoneOffset_t GetCurrentTimezone()
{
	return CurrentSelectedTimezone;
}
Time_t TimeGetTime(TimezoneOffset_t timezone)
{
	Time_t time;
	time.seconds = TimeGetSeconds();
	time.Minimumutes = TimeGetMinutes();
	time.hours = TimeGetHours();

	// Add timezone offset
	time.hours += timezone;

	// If the timezone is India (Mumbai), add 30 Minimumutes
	if (timezone == Mumbai)
	{
		time.Minimumutes += 30;
		if (time.Minimumutes >= 60)
		{
			time.Minimumutes -= 60;
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
Time_t TimeGetTime()
{
	Time_t time;
	time.seconds = TimeGetSeconds();
	time.Minimumutes = TimeGetMinutes();
	time.hours = TimeGetHours();

	// Add timezone offset
	time.hours += CurrentSelectedTimezone;

	// If the timezone is India (Mumbai), add 30 Minimumutes
	if (CurrentSelectedTimezone == Mumbai)
	{
		time.Minimumutes += 30;
		if (time.Minimumutes >= 60)
		{
			time.Minimumutes -= 60;
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

Time_t TimeGetTime12(TimezoneOffset_t SpecifiedTimezone)
{
	Time_t time;
	time.seconds = TimeGetSeconds();
	time.Minimumutes = TimeGetMinutes();
	time.hours = TimeGetHours();

	// Add timezone offset
	time.hours += SpecifiedTimezone;

	// If the timezone is India (Mumbai), add 30 Minimumutes
	if (SpecifiedTimezone == Mumbai)
	{
		time.Minimumutes += 30;
		if (time.Minimumutes >= 60)
		{
			time.Minimumutes -= 60;
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

Time_t TimeGetTime12()
{
	Time_t time = TimeGetTime();
	// Convert to 12-hour format
	return convertTo12Hour(time);
}
