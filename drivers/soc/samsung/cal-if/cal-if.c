#include <linux/module.h>
#include <linux/exynos-ss.h>
#include <soc/samsung/ect_parser.h>
#include <soc/samsung/cal-if.h>

#include "pwrcal-env.h"
#include "pwrcal-rae.h"
#include "cmucal.h"
#include "ra.h"
#include "acpm_dvfs.h"
#include "fvmap.h"
#include "asv.h"

#include "pmucal_system.h"
#include "pmucal_local.h"
#include "pmucal_cpu.h"
#include "pmucal_cp.h"
#include "pmucal_gnss.h"
#include "pmucal_rae.h"

unsigned int cal_clk_is_enabled(unsigned int id)
{
	return 0;
}

unsigned long cal_dfs_get_max_freq(unsigned int id)
{
	return vclk_get_max_freq(id);
}

unsigned long cal_dfs_get_min_freq(unsigned int id)
{
	return vclk_get_min_freq(id);
}

unsigned int cal_dfs_get_lv_num(unsigned int id)
{
	return vclk_get_lv_num(id);
}

int cal_dfs_get_bigturbo_max_freq(unsigned int *table)
{
	return vclk_get_bigturbo_table(table);
}

int cal_dfs_set_rate(unsigned int id, unsigned long rate)
{
	struct vclk *vclk;
	int ret;

	if (IS_ACPM_VCLK(id)) {
		ret = exynos_acpm_set_rate(GET_IDX(id), rate);
		if (!ret) {
			vclk = cmucal_get_node(id);
			if (vclk)
				vclk->vrate = rate;
		}
	} else {
		ret = vclk_set_rate(id, rate);
	}

	return ret;
}

int cal_dfs_set_rate_switch(unsigned int id, unsigned long switch_rate)
{
	int ret = 0;

	ret = vclk_set_rate_switch(id, switch_rate);

	return ret;
}

int cal_dfs_set_rate_restore(unsigned int id, unsigned long switch_rate)
{
	int ret = 0;

	ret = vclk_set_rate_restore(id, switch_rate);

	return ret;
}

unsigned long cal_dfs_cached_get_rate(unsigned int id)
{
	int ret;

	ret = vclk_get_rate(id);

	return ret;
}

unsigned long cal_dfs_get_rate(unsigned int id)
{
	int ret;

	ret = vclk_recalc_rate(id);

	return ret;
}

int cal_dfs_get_rate_table(unsigned int id, unsigned long *table)
{
	int ret;

	ret = vclk_get_rate_table(id, table);

	return ret;
}

int cal_clk_setrate(unsigned int id, unsigned long rate)
{
	int ret = -EINVAL;

	ret = vclk_set_rate(id, rate);

	return ret;
}

unsigned long cal_clk_getrate(unsigned int id)
{
	int ret = 0;

	ret = vclk_recalc_rate(id);

	return ret;
}

int cal_clk_enable(unsigned int id)
{
	int ret = 0;

	ret = vclk_set_enable(id);

	return ret;
}

int cal_clk_disable(unsigned int id)
{
	int ret = 0;

	ret = vclk_set_disable(id);

	return ret;
}

int cal_qch_init(unsigned int id, unsigned int use_qch)
{
	int ret = 0;

	ret = ra_set_qch(id, use_qch, 1, 0);

	return ret;
}

unsigned int cal_dfs_get_boot_freq(unsigned int id)
{
	return vclk_get_boot_freq(id);
}

unsigned int cal_dfs_get_resume_freq(unsigned int id)
{
	return vclk_get_resume_freq(id);
}

int cal_pd_control(unsigned int id, int on)
{
	unsigned int index;

	if ((id & 0xFFFF0000) != BLKPWR_MAGIC)
		return -1;

	index = id & 0x0000FFFF;

	if (on)
		return pmucal_local_enable(index);
	else
		return pmucal_local_disable(index);
}

int cal_pd_status(unsigned int id)
{
	unsigned int index;

	if ((id & 0xFFFF0000) != BLKPWR_MAGIC)
		return -1;

	index = id & 0x0000FFFF;

	return pmucal_local_is_enabled(index);
}

int cal_pm_enter(int mode)
{
	return pmucal_system_enter(mode);
}

int cal_pm_exit(int mode)
{
	return pmucal_system_exit(mode);
}

int cal_pm_earlywakeup(int mode)
{
	return pmucal_system_earlywakeup(mode);
}

int cal_cpu_enable(unsigned int cpu)
{
	return pmucal_cpu_enable(cpu);
}

int cal_cpu_disable(unsigned int cpu)
{
	return pmucal_cpu_disable(cpu);
}

int cal_cpu_status(unsigned int cpu)
{
	return pmucal_cpu_is_enabled(cpu);
}

int cal_cluster_enable(unsigned int cluster)
{
	return pmucal_cpu_cluster_enable(cluster);
}

int cal_cluster_disable(unsigned int cluster)
{
	return pmucal_cpu_cluster_disable(cluster);
}

int cal_cluster_status(unsigned int cluster)
{
	return pmucal_cpu_cluster_is_enabled(cluster);
}

int cal_dfs_get_asv_table(unsigned int id, unsigned int *table)
{
	return fvmap_get_voltage_table(id, table);
}

void cal_dfs_set_volt_margin(unsigned int id, int volt)
{
	if (IS_ACPM_VCLK(id))
		exynos_acpm_set_volt_margin(id, volt);
}

int cal_dfs_get_rate_asv_table(unsigned int id,
					struct dvfs_rate_volt *table)
{
	unsigned long rate[48];
	unsigned int volt[48];
	int num_of_entry;
	int idx;

	num_of_entry = cal_dfs_get_rate_table(id, rate);
	if (num_of_entry == 0)
		return 0;

	if (num_of_entry != cal_dfs_get_asv_table(id, volt))
		return 0;

	for (idx = 0; idx < num_of_entry; idx++) {
		table[idx].rate = rate[idx];
		table[idx].volt = volt[idx];
/*
		if(table[idx].rate==2496000||rate[idx]==2496000){
			table[idx].volt=1300000;
			volt[idx]=1300000;//1143750  all not work
}
		if(table[idx].rate==2392000||rate[idx]==2392000)
			{
			table[idx].volt=1300000;
			volt[idx]=1300000;//1143750
			}
	if(table[idx].rate==2288000||rate[idx]==2288000)
			{
			table[idx].volt=1300000;
			volt[idx]=1300000;//1143750
			}
		if(table[idx].rate==1898000||rate[idx]==1898000){
			table[idx].volt=1300000;
			volt[idx]=1300000;
}
		if(table[idx].rate==2002000||rate[idx]==2002000){
			table[idx].volt=1300000;
			volt[idx]=1300000;
}
		if(table[idx].rate==2093000||rate[idx]==2002000){
			table[idx].volt=1300000;
			volt[idx]=1300000;
}
		if(table[idx].rate==1898000||rate[idx]==1898000){
			table[idx].volt=1300000;
			volt[idx]=1300000;
}
	pr_info("rate[idx] : %u kHz - volt[idx] : %u Uv- topser99asv\n",rate[idx],volt[idx]);//hope*/
	}

	return num_of_entry;
}

int cal_asv_get_ids_info(unsigned int id)
{
	return asv_get_ids_info(id);
}

int cal_asv_get_grp(unsigned int id)
{
	return asv_get_grp(id);
}

int cal_asv_get_tablever(void)
{
	return asv_get_table_ver();
}

#ifdef CONFIG_CP_PMUCAL
void cal_cp_init(void)
{
	pmucal_cp_init();
}

int cal_cp_status(void)
{
	return pmucal_cp_status();
}

void cal_cp_reset_assert(void)
{
	pmucal_cp_reset_assert();
}

void cal_cp_reset_release(void)
{
	pmucal_cp_reset_release();
}

void cal_cp_active_clear(void)
{
	pmucal_cp_active_clear();
}

void cal_cp_reset_req_clear(void)
{
	pmucal_cp_reset_req_clear();
}
#endif

#ifdef CONFIG_GNSS_PMUCAL
void cal_gnss_init(void)
{
	pmucal_gnss_init();
}

int cal_gnss_status(void)
{
	return pmucal_gnss_status();
}

void cal_gnss_reset_assert(void)
{
	pmucal_gnss_reset_assert();
}

void cal_gnss_reset_release(void)
{
	pmucal_gnss_reset_release();
}

void cal_gnss_active_clear(void)
{
	pmucal_gnss_active_clear();
}

void cal_gnss_reset_req_clear(void)
{
	pmucal_gnss_reset_req_clear();
}
#endif

int __init cal_if_init(void *dev)
{
	static int cal_initialized;
	int ret;

	if (cal_initialized == 1)
		return 0;

	ect_parse_binary_header();

	vclk_initialize();

	if (cal_data_init)
		cal_data_init();

	ret = pmucal_rae_init();
	if (ret < 0)
		return ret;

	ret = pmucal_system_init();
	if (ret < 0)
		return ret;

	ret = pmucal_local_init();
	if (ret < 0)
		return ret;

	ret = pmucal_cpu_init();
	if (ret < 0)
		return ret;

#ifdef CONFIG_CP_PMUCAL
	ret = pmucal_cp_initialize();
	if (ret < 0)
		return ret;
#endif

#ifdef CONFIG_GNSS_PMUCAL
	ret = pmucal_gnss_initialize();
	if (ret < 0)
		return ret;
#endif

	exynos_acpm_set_device(dev);

	cal_initialized = 1;

	return 0;
}

