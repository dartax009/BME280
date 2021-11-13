#include "BME280.h"
#include "../../tires/i2c/i2c.h"

static s_trim_table trim_table;

uint8_t init_BME280_i2c (const uint8_t addr)
{
    uint8_t t_buff	= 0;

	if ( a_read_i2c_8b(&t_buff, REG_ID_BME280, addr) )
		return 1; 		//Не удалось прочитать ID датчика

	if (t_buff != VALUE_ID_BME280)
		return 2;		//Прочетанный ID не совпадает с ожидаемым

	if ( a_write_reg_i2c_8b(VALUE_RESET_BME280, REG_RESET_BME280, addr) )
		return 3;		//Не удачный сброс датчика

	do
	{
		if ( check_status_BME280_i2c (addr, &t_buff) )
			return 3;	//Не удалось прочитать статус
	}
	while (t_buff & M_STATUS_COPY_BME280);

	read_coeff_BME280_i2c(addr);

    return 0;
}

uint8_t check_status_BME280_i2c (const uint8_t addr, uint8_t *data)
{
	if ( a_read_i2c_8b(data, REG_STATUS_BME280, addr) )
		return 1;		//Не удалось прочитать статус

	*data &= M_STATUS_SIGN_BME280;
	return 0;
}

void read_coeff_BME280_i2c (const uint8_t addr)
{
	uint8_t t_buff[2] = {0};

	a_read_BME280_16b_r(&trim_table.dig_T1, REG_DIG_T1_BME280, addr);
	a_read_BME280_16b_r( (uint16_t*)&trim_table.dig_T2, REG_DIG_T2_BME280, addr);
	a_read_BME280_16b_r( (uint16_t*)&trim_table.dig_T3, REG_DIG_T3_BME280, addr);

	a_read_BME280_16b_r(&trim_table.dig_P1, REG_DIG_P1_BME280, addr);
	a_read_BME280_16b_r( (uint16_t*)&trim_table.dig_P2, REG_DIG_P2_BME280, addr);
	a_read_BME280_16b_r( (uint16_t*)&trim_table.dig_P3, REG_DIG_P3_BME280, addr);
	a_read_BME280_16b_r( (uint16_t*)&trim_table.dig_P4, REG_DIG_P4_BME280, addr);
	a_read_BME280_16b_r( (uint16_t*)&trim_table.dig_P5, REG_DIG_P5_BME280, addr);
	a_read_BME280_16b_r( (uint16_t*)&trim_table.dig_P6, REG_DIG_P6_BME280, addr);
	a_read_BME280_16b_r( (uint16_t*)&trim_table.dig_P7, REG_DIG_P7_BME280, addr);
	a_read_BME280_16b_r( (uint16_t*)&trim_table.dig_P8, REG_DIG_P8_BME280, addr);
	a_read_BME280_16b_r( (uint16_t*)&trim_table.dig_P9, REG_DIG_P9_BME280, addr);

	a_read_i2c_8b(&trim_table.dig_H1, REG_DIG_H1_BME280, addr);
	a_read_BME280_16b_r( (uint16_t*)&trim_table.dig_H2, REG_DIG_H2_BME280, addr);
	a_read_i2c_8b(&trim_table.dig_H3, REG_DIG_H3_BME280, addr);

	a_read_i2c_8b(&t_buff[0], REG_DIG_H4_BME280, addr);
	a_read_i2c_8b(&t_buff[1], REG_DIG_H4_BME280+1, addr);
	trim_table.dig_H4 = (t_buff[0] << 4) | (t_buff[1] & 0xF);

	a_read_i2c_8b(&t_buff[0], REG_DIG_H5_BME280+1, addr);
	a_read_i2c_8b(&t_buff[1], REG_DIG_H5_BME280, addr);
	trim_table.dig_H5 = (t_buff[0] << 4) | (t_buff[1] >> 4);

	a_read_i2c_8b( (uint8_t*)&trim_table.dig_H6, REG_DIG_H6_BME280, addr);

	return;
}

uint8_t set_standby_BME280_i2c (const uint8_t addr, const uint8_t stend)
{
	uint8_t v_reg = 0;

	if ( a_read_i2c_8b(&v_reg, REG_CONFIG_BME280, addr) )
		return 1;				//Не удалось конфигурационный регистр

	v_reg &= ~M_CONFIG_STANDBY_BME280;
	v_reg |= stend & M_CONFIG_STANDBY_BME280;

	if ( a_write_reg_i2c_8b(v_reg, REG_CONFIG_BME280, addr) )
		return 2;				//Не удалось отправить задержку

	return 0;
}

uint8_t set_filter_BME280_i2c (const uint8_t addr, const uint8_t filt)
{
	uint8_t v_reg = 0;

	if ( a_read_i2c_8b(&v_reg, REG_CONFIG_BME280, addr) )
		return 1;				//Не удалось конфигурационный регистр

	v_reg &= ~M_CONFIG_FILTER_BME280;
	v_reg |= filt & M_CONFIG_FILTER_BME280;

	if ( a_write_reg_i2c_8b(v_reg, REG_CONFIG_BME280, addr) )
		return 2;				//Не удалось отправить фильтр

	return 0;
}

uint8_t set_hum_overs_BME280_i2c (const uint8_t addr, const uint8_t over)
{
	uint8_t v_reg = 0;

	if ( a_read_i2c_8b(&v_reg, REG_CTRL_HUMID_BME280, addr) )
		return 1;				//Не удалось конфигурационный регистр

	v_reg &= ~M_CTRL_HUM_BME280;
	v_reg |= over & M_CTRL_HUM_BME280;

	if ( a_write_reg_i2c_8b(v_reg, REG_CTRL_HUMID_BME280, addr) )
		return 2;				//Не удалось отправить фильтр

	if ( a_read_i2c_8b(&v_reg, REG_CTRL_MEAS_BME280, addr) )
		return 3;				//Ошибка установки параметров

	if ( a_write_reg_i2c_8b(v_reg, REG_CTRL_MEAS_BME280, addr) )
		return 3;				//Ошибка установки параметров

	return 0;
}

uint8_t set_temp_overs_BME280_i2c (const uint8_t addr, const uint8_t over)
{
	uint8_t v_reg = 0;

	if ( a_read_i2c_8b(&v_reg, REG_CTRL_MEAS_BME280, addr) )
		return 1;				//Не удалось конфигурационный регистр

	v_reg &= ~M_CTRL_MEAS_TEMP_BME280;
	v_reg |= over & M_CTRL_MEAS_TEMP_BME280;

	if ( a_write_reg_i2c_8b(v_reg, REG_CTRL_MEAS_BME280, addr) )
		return 2;				//Не удалось отправить фильтр

	return 0;
}

uint8_t set_pres_overs_BME280_i2c (const uint8_t addr, const uint8_t over)
{
	uint8_t v_reg = 0;

	if ( a_read_i2c_8b(&v_reg, REG_CTRL_MEAS_BME280, addr) )
		return 1;				//Не удалось конфигурационный регистр

	v_reg &= ~M_CTRL_MEAS_PRES_BME280;
	v_reg |= over & M_CTRL_MEAS_PRES_BME280;

	if ( a_write_reg_i2c_8b(v_reg, REG_CTRL_MEAS_BME280, addr) )
		return 2;				//Не удалось отправить фильтр

	return 0;
}

uint8_t set_mode_BME280_i2c (const uint8_t addr, const uint8_t mode)
{
	uint8_t v_reg = 0;

	if ( a_read_i2c_8b(&v_reg, REG_CTRL_MEAS_BME280, addr) )
		return 1;				//Не удалось конфигурационный регистр

	v_reg &= ~M_CTRL_MEAS_MODE_BME280;
	v_reg |= mode & M_CTRL_MEAS_MODE_BME280;

	if ( a_write_reg_i2c_8b(v_reg, REG_CTRL_MEAS_BME280, addr) )
		return 2;				//Не удалось отправить фильтр

	return 0;
}

uint8_t read_temp_BME280_i2c (int32_t *temp, const uint8_t addr, uint8_t conv)
{
	int32_t r_temp = 0;
	int32_t val1 = 0, val2 = 0;
	if ( a_read_i2c_24b ( (uint32_t*)&r_temp, REG_TEMP_BME280, addr) )
		return 1;			//Не удачное чтение регистар

	r_temp >>= 4;

	val1 = ((((r_temp>>3) - ((int32_t)trim_table.dig_T1 <<1))) * ((int32_t)trim_table.dig_T2)) >> 11;
	val2 = (((((r_temp>>4) - ((int32_t)trim_table.dig_T1)) * ((r_temp>>4) - ((int32_t)trim_table.dig_T1))) >> 12) * ((int32_t)trim_table.dig_T3)) >> 14;

	*(int32_t *)temp = val1 + val2;
	if (conv)
	{
		*(int32_t *)temp = ((*(int32_t *)temp * 5 + 128) >> 8);
		*(int32_t *)temp /= 100;
	}
	return 0;
}

uint8_t read_pres_BME280_i2c (int32_t *pres, const uint8_t addr, uint8_t conv)
{
	int32_t temp = 0;
	if ( read_temp_BME280_i2c (&temp, addr, 0) )
		return 2;			//Не удалось считать температуру

	uint32_t r_pres = 0;
	int64_t val1 = 0, val2 = 0, p = 0;
	if ( a_read_i2c_24b ( (uint32_t*)&r_pres, REG_PRES_BME280, addr) )
		return 1;			//Не удачное чтение регистар

	r_pres >>=4;

	val1 = ((int64_t)temp) - 128000;
	val2 = val1 * val1 * (int64_t)trim_table.dig_P6;
	val2 = val2 + ((val1*(int64_t)trim_table.dig_P5)<<17);
	val2 = val2 + (((int64_t)trim_table.dig_P4)<<35);
	val1 = ((val1 * val1 * (int64_t)trim_table.dig_P3)>>8) + ((val1 * (int64_t)trim_table.dig_P2)<<12);
	val1 = (((((int64_t)1)<<47)+val1))*((int64_t)trim_table.dig_P1)>>33;

	if (val1 == 0)
		return 3;		//Деление на 0

	p = 1048576 - r_pres;
	p = (((p << 31) - val2) * 3125) / val1;
	val1 = (((int64_t)trim_table.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
	val2 = (((int64_t)trim_table.dig_P8) * p) >> 19;
	*pres = ((p + val1 + val2) >> 8) + ((int64_t)trim_table.dig_P7 << 4);
	// *pres = ((p >> 8) * 1000) + (((p & 0xff) * 390625) / 100000);
	if (conv)
		*pres /= 256;

	return 0;
}

uint8_t read_hum_BME280_i2c (int32_t *hum, const uint8_t addr, uint8_t conv)
{
	int32_t temp = 0;
	if ( read_temp_BME280_i2c (&temp, addr, 0) )
		return 2;			//Не удалось считать температуру

	uint32_t r_hum = 0;
	int64_t val1 = 0;
	if ( a_read_i2c_16b ( (uint16_t*)&r_hum, REG_HUM_BME280, addr) )
		return 1;			//Не удачное чтение регистар

	val1 = (temp - ((int32_t)76800));

	val1 = (((((r_hum << 14) - (((int32_t)trim_table.dig_H4) << 20) - (((int32_t)trim_table.dig_H5) * val1)) + ((int32_t)16384)) >> 15) *
	(((((((val1 * ((int32_t)trim_table.dig_H6)) >> 10) *
	(((val1 * ((int32_t)trim_table.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
	((int32_t)2097152)) * ((int32_t)trim_table.dig_H2) + 8192) >> 14));

	val1 = (val1 - (((((val1 >> 15) * (val1 >> 15)) >> 7) * ((int32_t)trim_table.dig_H1)) >> 4));

	val1 = (val1 < 0) ? 0 : val1;
	val1 = (val1 > 419430400) ? 419430400 : val1;

	*hum = val1>>12;
	if (conv)
		*hum /= 1024;

	return 0;
}

uint8_t a_read_BME280_16b_r (uint16_t *data, uint8_t reg, uint8_t addr)
{
	if ( a_read_i2c_16b(data, reg, addr) )
		return 1;
	*data = (*data >> 8) | (*data << 8);
	return 0;
}
