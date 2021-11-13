#ifndef _BME_280_H
#define _BME_280_H

#include <stdint.h>

/**
 * @brief Адреса регистров BME280
 *
 */
#define REG_ID_BME280			0xD0		///> Регистр ID датчика BME280
#define REG_STATUS_BME280		0xF3		///> Статусный регистр BME280
#define REG_RESET_BME280		0xE0		///> Регистр перезапуска BME280
#define REG_CONFIG_BME280		0xF5		///> Регистр конфигурации BME280
#define REG_CTRL_HUMID_BME280	0xF2		///> Регистр контроля влажности BME280
#define REG_CTRL_MEAS_BME280	0xF4		///> Регистр контроля измерений BM280
#define REG_TEMP_BME280			0xFA		///> Регистр температуры
#define REG_PRES_BME280			0xF7		///> Регистр давления
#define REG_HUM_BME280			0xFD		///> Регистр влажности

#define REG_DIG_T1_BME280	0x88
#define REG_DIG_T2_BME280	0x8A
#define REG_DIG_T3_BME280	0x8C
#define REG_DIG_P1_BME280	0x8E
#define REG_DIG_P2_BME280	0x90
#define REG_DIG_P3_BME280	0x92
#define REG_DIG_P4_BME280	0x94
#define REG_DIG_P5_BME280	0x96
#define REG_DIG_P6_BME280	0x98
#define REG_DIG_P7_BME280	0x9A
#define REG_DIG_P8_BME280	0x9C
#define REG_DIG_P9_BME280	0x9E
#define REG_DIG_H1_BME280	0xA1
#define REG_DIG_H2_BME280	0xE1
#define REG_DIG_H3_BME280	0xE3
#define REG_DIG_H4_BME280	0xE4
#define REG_DIG_H5_BME280	0xE5
#define REG_DIG_H6_BME280	0xE7

/**
 * @brief Заготовленные значения для BME280
 *
 */
#define VALUE_ID_BME280			0x60		///> ID BME280
#define VALUE_RESET_BME280		0xB6		///> Значение для перезагрузки BME280

#define STANDBY_0_5_BME280		0x00		///> Ожидание между замерами 0,5 мс
#define STANDBY_62_5_BME280		0x20		///> Ожидание между замерами 62,5 мс
#define STANDBY_125_0_BME280	0x40		///> Ожидание между замерами 125 мс
#define STANDBY_250_0_BME280	0x60		///> Ожидание между замерами 250 мс
#define STANDBY_500_0_BME280	0x80		///> Ожидание между замерами 500 мс
#define STANDBY_1000_0_BME280	0xA0		///> Ожидание между замерами 1000 мс
#define STANDBY_10_0_BME280		0xC0		///> Ожидание между замерами 10 мс
#define STANDBY_20_0_BME280		0xE0		///> Ожидание между замерами 20 мс

#define FILTER_OFF_BME280		0x00		///> Фильтр отключен
#define FILTER_2_BME280			0x04		///> Фильтр 2
#define FILTER_4_BME280			0x08		///> Фильтр 4
#define FILTER_8_BME280			0x0C		///> Фильтр 8
#define FILTER_16_BME280		0x10		///> Фильтр 16

#define HUM_SKIP_BME280			0x00		///> Оверсемплинг влажность отключена
#define HUM_OVERS_1_BME280		0x01		///> Оверсемплинг влажность x1
#define HUM_OVERS_2_BME280		0x02		///> Оверсемплинг влажность x2
#define HUM_OVERS_4_BME280		0x03		///> Оверсемплинг влажность x4
#define HUM_OVERS_8_BME280		0x04		///> Оверсемплинг влажность x8
#define HUM_OVERS_16_BME280		0x05		///> Оверсемплинг влажность x16

#define TEMP_SKIP_BME280		0x00		///> Оверсемплинг температуры отключен
#define TEMP_OVERS_1_BME280		0x20		///> Оверсемплинг температуры x1
#define TEMP_OVERS_2_BME280		0x40		///> Оверсемплинг температуры x2
#define TEMP_OVERS_4_BME280		0x60		///> Оверсемплинг температуры x4
#define TEMP_OVERS_8_BME280		0x80		///> Оверсемплинг температуры x8
#define TEMP_OVERS_16_BME280	0xA0		///> Оверсемплинг температуры x16

#define PRES_SKIP_BME280		0x00		///> Оверсемплинг давления отключен
#define PRES_OVERS_1_BME280		0x04		///> Оверсемплинг давления x1
#define PRES_OVERS_2_BME280		0x08		///> Оверсемплинг давления x2
#define PRES_OVERS_4_BME280		0x0C		///> Оверсемплинг давления x4
#define PRES_OVERS_8_BME280		0x10		///> Оверсемплинг давления x8
#define PRES_OVERS_16_BME280	0x14		///> Оверсемплинг давления x16

#define MODE_SLEEP_BME280		0x00		///> Режим сна
#define MODE_FORC_BME280		0x01		///> Режим принудительный
#define MODE_NORM_BME280		0x03		///> Режим нормальный

/**
 * @brief Маски для регистров BME280
 *
 */
#define M_STATUS_COPY_BME280		0x01		///> Регистр "статуса" бит 0 "копирование данных"
#define M_STATUS_TRANSFORM_BME280	0x08		///> Регистр "статуса" бит 3 "производится конвертация данных"
#define M_STATUS_SIGN_BME280		0x09		///> Значащие биты регистра "статус"

#define M_CONFIG_STANDBY_BME280		0xE0		///> Регистр "конфигурации" бит 5-7 "ожидание"
#define M_CONFIG_FILTER_BME280		0x1C		///> Регистр "конфигурации" бит 2-4 "фильтр"

#define M_CTRL_HUM_BME280			0x07		///> Регистр "контроль влажности" бит 0-2 "настройка влажности"

#define M_CTRL_MEAS_TEMP_BME280		0xE0		///> Регистр "контроль измерений" бит 5-7 "настройка тепературы"
#define M_CTRL_MEAS_PRES_BME280		0x1C		///> Регистр "контроль измерений" бит 2-4 "настройка давления"
#define M_CTRL_MEAS_MODE_BME280		0x03		///> Регистр "контроль измерений" бит 0-1 "настройка режима"

typedef struct _s_trim_table
{
	uint16_t	dig_T1;
	int16_t		dig_T2;
	int16_t		dig_T3;
	uint16_t	dig_P1;
	int16_t		dig_P2;
	int16_t		dig_P3;
	int16_t		dig_P4;
	int16_t		dig_P5;
	int16_t		dig_P6;
	int16_t		dig_P7;
	int16_t		dig_P8;
	int16_t		dig_P9;
	uint8_t		dig_H1;
	int16_t		dig_H2;
	uint8_t		dig_H3;
	int16_t		dig_H4;
	int16_t		dig_H5;
	int8_t		dig_H6;

} s_trim_table;

uint8_t init_BME280_i2c (const uint8_t addr);
uint8_t check_status_BME280_i2c (const uint8_t addr, uint8_t *data);
void read_coeff_BME280_i2c (const uint8_t addr);
uint8_t set_standby_BME280_i2c (const uint8_t addr, const uint8_t stend);
uint8_t set_filter_BME280_i2c (const uint8_t addr, const uint8_t filt);
uint8_t set_hum_overs_BME280_i2c (const uint8_t addr, const uint8_t over);
uint8_t set_temp_overs_BME280_i2c (const uint8_t addr, const uint8_t over);
uint8_t set_pres_overs_BME280_i2c (const uint8_t addr, const uint8_t over);
uint8_t set_mode_BME280_i2c (const uint8_t addr, const uint8_t mode);
uint8_t read_temp_BME280_i2c (int32_t *temp, const uint8_t addr, uint8_t conv);
uint8_t read_pres_BME280_i2c (int32_t *pres, const uint8_t addr, uint8_t conv);
uint8_t read_hum_BME280_i2c (int32_t *hum, const uint8_t addr, uint8_t conv);

uint8_t a_read_BME280_16b_r (uint16_t *data, uint8_t reg, uint8_t addr);

#endif