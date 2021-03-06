#include "SA.h"
#include "Look.h"
#include <stdio.h>
extern "C" SeeThis mdata; //new global data structure



//////////////////////////////////////////////////////////////////////
double get_cost(void)
{
	int i;
	double COST = 0.0;
	double error_hip_r_ang = 0.0;
	double error_knee_r_ang = 0.0;
	double error_ankle_r_ang = 0.0;
	double error_hip_l_ang = 0.0;
	double error_knee_l_ang = 0.0;
	double error_ankle_l_ang = 0.0;
	double error_hip_tx = 0.0;
	double error_hip_ty = 0.0;
	double error_hip_l_trq = 0.0; 
	double error_knee_l_trq = 0.0;
	double error_ankle_l_trq = 0.0; 
	double error_hip_l_pwr = 0.0;
	double error_knee_l_pwr = 0.0;
	double error_ankle_l_pwr = 0.0;
	double error_grfz_r = 0.0;
	double error_grfz_l = 0.0;
	double error_grfx_l = 0.0;
	double error_grfx_r = 0.0; //this does not have exp.data, but it's ready 
	double error_ankle_l_vel = 0.0;
	double error_segme = 0.0;
	double error_pelvis_rot = 0.0;
	double error_extpwr = 0.0; //left extpwr (added 9-1-03)
	double error_sysme = 0.0; //left extpwr (added 9-15-03)
	double error_syske = 0.0; //left extpwr (added 9-15-03)
	double error_syspe = 0.0; //left extpwr (added 9-15-03)
	double mus_power =0.0; //added 8-17-04
	double error_Lgrf_on = 0.0; //added 10-21-04
	double mus_exc =0.0; //added 8-06-07


	double error_hip_r_ang_adjust = 0.0;
	double error_knee_r_ang_adjust = 0.0;
	double error_ankle_r_ang_adjust = 0.0;
	double error_hip_l_ang_adjust = 0.0;
	double error_knee_l_ang_adjust = 0.0;
	double error_ankle_l_ang_adjust = 0.0;
	double error_hip_tx_adjust = 0.0;
	double error_hip_ty_adjust = 0.0;
	double error_hip_l_trq_adjust = 0.0; 
	double error_knee_l_trq_adjust = 0.0;
	double error_ankle_l_trq_adjust = 0.0; 
	double error_hip_l_pwr_adjust = 0.0;
	double error_knee_l_pwr_adjust = 0.0;
	double error_ankle_l_pwr_adjust = 0.0;
	double error_grfz_r_adjust = 0.0;
	double error_grfz_l_adjust = 0.0;
	double error_grfx_l_adjust = 0.0;
	double error_grfx_r_adjust = 0.0;
	double error_ankle_l_vel_adjust = 0.0;
	double error_segme_adjust = 0.0;
	double error_pelvis_rot_adjust = 0.0;
	double error_extpwr_adjust = 0.0; //added 9-1-03
	double error_sysme_adjust = 0.0; //added 9-15-03
	double error_syske_adjust = 0.0; //added 9-15-03
	double error_syspe_adjust = 0.0; //added 9-15-03
	double mus_power_adjust = 0.0; //added 8-17-04
	double error_Lgrf_on_adjust = 0.0; //added 10-21-04
	double mus_exc_adjust = 0.0; //added 8-06-07

	
	error_Lgrf_on = pow((mdata.Lgrf_on - 50.0),2.0);

	for(i=1;i<N_cost_step;i++){ //the value for the beginnig may bave to be adjusted

		//muscle power (added 8-17-04)
		mus_power = mus_power + mdata.muspower[i];

		//muscle excitation level (added 8-06-07)
		mus_exc = mus_exc + mdata.musexc[i];


		//GRF_r
		if((i>=101)||(i<=65)){
			error_grfz_r = error_grfz_r 
				+ pow((mdata.exp_cost_ave[8][i]-mdata.grfz_r[i])
					/mdata.exp_cost_sd[8][i],2.0);
		}
		else{
			error_grfz_r = error_grfz_r
				+ pow((mdata.exp_cost_ave[8][i]-mdata.grfz_r[i])/0.01,2.0);
		}

		//GRF_l, ankle trq & pwr, extpwr
		if((i<=15)||((i>=50)&&(i<=115))){
			error_ankle_l_trq = error_ankle_l_trq
				+ pow((mdata.exp_cost_ave[11][i]-mdata.ankle_l_trq[i])
					/mdata.exp_cost_sd[11][i],2.0);
			error_ankle_l_pwr = error_ankle_l_pwr
				+ pow((mdata.exp_cost_ave[15][i]-mdata.ankle_l_pwr[i])
					/mdata.exp_cost_sd[15][i],2.0);
	
			//if(i>=50 && i<=75){
			//	error_grfx_l = error_grfx_l
			//	+ 5.0*pow((mdata.exp_cost_ave[16][i]-mdata.grfx_l[i])
			//		/mdata.exp_cost_sd[16][i],2.0);
			//	error_grfz_l = error_grfz_l
			//	+ 5.0*pow((mdata.exp_cost_ave[12][i]-mdata.grfz_l[i])
			//		/mdata.exp_cost_sd[12][i],2.0);
			//}
			//else if(i>=75 && i<=115){
			//	error_grfx_l = error_grfx_l
			//	+ 2.0*pow((mdata.exp_cost_ave[16][i]-mdata.grfx_l[i])
			//		/mdata.exp_cost_sd[16][i],2.0);
			//	error_grfz_l = error_grfz_l
			//	+ 2.0*pow((mdata.exp_cost_ave[12][i]-mdata.grfz_l[i])
			//		/mdata.exp_cost_sd[12][i],2.0);
			//}
			//else{
				error_grfx_l = error_grfx_l
				+ pow((mdata.exp_cost_ave[16][i]-mdata.grfx_l[i])
					/mdata.exp_cost_sd[16][i],2.0);
				error_grfz_l = error_grfz_l
				+ pow((mdata.exp_cost_ave[12][i]-mdata.grfz_l[i])
					/mdata.exp_cost_sd[12][i],2.0);
			//}
	
			
			if(i>=50 && i<=75){
				error_extpwr = error_extpwr
				+ 50.0*pow((mdata.exp_cost_ave[19][i]-mdata.extpwr[i])
					/mdata.exp_cost_sd[19][i],2.0); //added 9-1-03
			}
			else{
				error_extpwr = error_extpwr
				+ pow((mdata.exp_cost_ave[19][i]-mdata.extpwr[i])
					/mdata.exp_cost_sd[19][i],2.0); //added 9-1-03
			}
		}
		else{
			error_ankle_l_trq = error_ankle_l_trq
				+ pow((mdata.exp_cost_ave[11][i]-mdata.ankle_l_trq[i])/0.01,2.0);
			error_ankle_l_pwr = error_ankle_l_pwr
				+ pow((mdata.exp_cost_ave[15][i]-mdata.ankle_l_pwr[i])/0.01,2.0);
			error_grfx_l = error_grfx_l
				+ pow((mdata.exp_cost_ave[16][i]-mdata.grfx_l[i])/0.01,2.0);
			error_grfz_l = error_grfz_l
				+ pow((mdata.exp_cost_ave[12][i]-mdata.grfz_l[i])/0.01,2.0);
			error_extpwr = error_extpwr
				+ pow((mdata.exp_cost_ave[19][i]-mdata.extpwr[i])/1.0,2.0);
		}

		//mechanical power
		if(i<100){
			error_segme = error_segme
				+ pow((mdata.segme_r[i] - mdata.segme_l[i+50]),2.0);
		}
		else{
			error_segme = error_segme
				+ pow((mdata.segme_r[i] - mdata.segme_l[i-50]),2.0);
		}



		// total system mechanical energy
		if(i>=100){
			error_sysme = error_sysme
				+ pow((mdata.sysme[i] - mdata.sysme[i-50]),2.0);
			error_syske = error_syske
				+ pow((mdata.syske[i] - mdata.syske[i-50]),2.0);
			error_syspe = error_syspe
				+ pow((mdata.syspe[i] - mdata.syspe[i-50]),2.0);
		}


	if(i>=1){
		if(i>=75 && i<=110){
			error_hip_r_ang = error_hip_r_ang 
			+ 15.0*pow((mdata.exp_cost_ave[0][i]-mdata.hip_r_ang[i])
				/mdata.exp_cost_sd[0][i],2.0);
		}
		else{
			error_hip_r_ang = error_hip_r_ang 
			+ pow((mdata.exp_cost_ave[0][i]-mdata.hip_r_ang[i])
				/mdata.exp_cost_sd[0][i],2.0);
		}

		//if(i>=100){
		//	error_knee_r_ang = error_knee_r_ang
		//	+ 2.0*pow((mdata.exp_cost_ave[1][i]-mdata.knee_r_ang[i])
		//		/mdata.exp_cost_sd[1][i],2.0);
		//}

		//else if(i>=75 && i<100){
		//	error_knee_r_ang = error_knee_r_ang
		//	+ 5.0*pow((mdata.exp_cost_ave[1][i]-mdata.knee_r_ang[i])
		//		/mdata.exp_cost_sd[1][i],2.0);
		//} 
		//else{
			error_knee_r_ang = error_knee_r_ang
			+ pow((mdata.exp_cost_ave[1][i]-mdata.knee_r_ang[i])
				/mdata.exp_cost_sd[1][i],2.0);
		//}

		
		if(i>=80 && i<=120){
			error_ankle_r_ang = error_ankle_r_ang
			+ 5.0*pow((mdata.exp_cost_ave[2][i]-mdata.ankle_r_ang[i])
				/mdata.exp_cost_sd[2][i],2.0);
		}

		else if(i>=30 && i<=70){
			error_ankle_r_ang = error_ankle_r_ang
			+ 15.0*pow((mdata.exp_cost_ave[2][i]-mdata.ankle_r_ang[i])
				/mdata.exp_cost_sd[2][i],2.0);
		}
		else{
			error_ankle_r_ang = error_ankle_r_ang
			+ pow((mdata.exp_cost_ave[2][i]-mdata.ankle_r_ang[i])
				/mdata.exp_cost_sd[2][i],2.0);
		}

		if((i>=25 && i<=60) || (i>=125 && i<=160)){
			error_hip_l_ang =  error_hip_l_ang
			+ 15.0*pow((mdata.exp_cost_ave[3][i]-mdata.hip_l_ang[i])
				/mdata.exp_cost_sd[3][i],2.0);
		}
		else{
			error_hip_l_ang =  error_hip_l_ang
			+ pow((mdata.exp_cost_ave[3][i]-mdata.hip_l_ang[i])
				/mdata.exp_cost_sd[3][i],2.0);
		}

		//if(i>=50 && i<=100){
		//	error_knee_l_ang = error_knee_l_ang
		//	+ 2.0*pow((mdata.exp_cost_ave[4][i]-mdata.knee_l_ang[i])
		//		/mdata.exp_cost_sd[4][i],2.0);
		//}

		//else if(i>=125){
		//	error_knee_l_ang = error_knee_l_ang
		//	+ 5.0*pow((mdata.exp_cost_ave[4][i]-mdata.knee_l_ang[i])
		//		/mdata.exp_cost_sd[4][i],2.0);
		//}
		//else{
			error_knee_l_ang = error_knee_l_ang
			+ pow((mdata.exp_cost_ave[4][i]-mdata.knee_l_ang[i])
				/mdata.exp_cost_sd[4][i],2.0);
		//}

	
		if((i>=30 && i<70) || i>=130){
			error_ankle_l_ang = error_ankle_l_ang 
			+ 5.0*pow((mdata.exp_cost_ave[5][i]-mdata.ankle_l_ang[i])
				/mdata.exp_cost_sd[5][i],2.0);
		}
		else if(i>=80 && i<=120){
			error_ankle_l_ang = error_ankle_l_ang 
			+ 15.0*pow((mdata.exp_cost_ave[5][i]-mdata.ankle_l_ang[i])
				/mdata.exp_cost_sd[5][i],2.0);
		}
		else{
			error_ankle_l_ang = error_ankle_l_ang 
			+ pow((mdata.exp_cost_ave[5][i]-mdata.ankle_l_ang[i])
				/mdata.exp_cost_sd[5][i],2.0);
		}
		


		error_hip_tx = error_hip_tx
			+ pow((mdata.exp_cost_ave[6][i]-mdata.hip_tx[i])
				/mdata.exp_cost_sd[6][i],2.0);
		error_hip_ty = error_hip_ty
			+ pow((mdata.exp_cost_ave[7][i]-(mdata.hip_ty[i]+(LEG_TY_DIFF)))
				/mdata.exp_cost_sd[7][i],2.0);
		error_pelvis_rot = error_pelvis_rot
			+ pow((mdata.exp_cost_ave[18][i]-mdata.pelvis_rot[i])
				/mdata.exp_cost_sd[18][i],2.0); 
	}


		error_hip_l_trq = error_hip_l_trq
			+ pow((mdata.exp_cost_ave[9][i]-mdata.hip_l_trq[i])
				/mdata.exp_cost_sd[9][i],2.0);
		error_knee_l_trq = error_knee_l_trq
			+ pow((mdata.exp_cost_ave[10][i]-mdata.knee_l_trq[i])
				/mdata.exp_cost_sd[10][i],2.0);
		error_hip_l_pwr = error_hip_l_pwr
			+ pow((mdata.exp_cost_ave[13][i]-mdata.hip_l_pwr[i])
				/mdata.exp_cost_sd[13][i],2.0);
		error_knee_l_pwr = error_knee_l_pwr
			+ pow((mdata.exp_cost_ave[14][i]-mdata.knee_l_pwr[i])
				/mdata.exp_cost_sd[14][i],2.0);		
		error_ankle_l_vel = error_ankle_l_vel
			+ pow((mdata.exp_cost_ave[17][i]-mdata.ankle_l_vel[i])
				/mdata.exp_cost_sd[17][i],2.0);
		
	
	}

	/*** This part is for writing SAoptERROR.dat ***/
	if(error_hip_r_ang>1.0e+12) error_hip_r_ang = 1.0e+12;
	if(error_knee_r_ang>1.0e+12) error_knee_r_ang = 1.0e+12;
	if(error_ankle_r_ang>1.0e+12) error_ankle_r_ang = 1.0e+12;
	if(error_hip_l_ang>1.0e+12) error_hip_l_ang = 1.0e+12;
	if(error_knee_l_ang>1.0e+12) error_knee_l_ang = 1.0e+12;
	if(error_ankle_l_ang>1.0e+12) error_ankle_l_ang = 1.0e+12;
	if(error_hip_tx>1.0e+12) error_hip_tx = 1.0e+12;
	if(error_hip_ty>1.0e+12) error_hip_ty = 1.0e+12;
	if(error_hip_l_trq>1.0e+12) error_hip_l_trq = 1.0e+12;
	if(error_knee_l_trq>1.0e+12) error_knee_l_trq = 1.0e+12;
	if(error_ankle_l_trq>1.0e+12) error_ankle_l_trq = 1.0e+12;
	if(error_hip_l_pwr>1.0e+12) error_hip_l_pwr = 1.0e+12;
	if(error_knee_l_pwr>1.0e+12) error_knee_l_pwr = 1.0e+12;
	if(error_ankle_l_pwr>1.0e+12) error_ankle_l_pwr = 1.0e+12;
	if(error_grfx_l>1.0e+12) error_grfx_l = 1.0e+12;
	if(error_grfz_l>1.0e+12) error_grfz_l = 1.0e+12;
	if(error_grfx_r>1.0e+12) error_grfx_r = 1.0e+12;
	if(error_grfz_r>1.0e+12) error_grfz_r = 1.0e+12;
	if(error_ankle_l_vel>1.0e+12) error_ankle_l_vel = 1.0e+12;
	if(error_segme>1.0e+12) error_segme = 1.0e+12;
	if(error_pelvis_rot>1.0e+12) error_pelvis_rot = 1.0e+12;
	if(error_extpwr>1.0e+12) error_extpwr = 1.0e+12; //added 9-1-03
	if(error_sysme>1.0e+12) error_sysme = 1.0e+12; //added 9-15-03
	if(error_syske>1.0e+12) error_syske = 1.0e+12; //added 9-15-03
	if(error_syspe>1.0e+12) error_syspe = 1.0e+12; //added 9-15-03


	////weight each error
	
	error_hip_r_ang_adjust = error_hip_r_ang * 1.0;
	error_knee_r_ang_adjust = error_knee_r_ang * 1.0;
	error_ankle_r_ang_adjust = error_ankle_r_ang * 3.0;
	error_hip_l_ang_adjust = error_hip_l_ang * 1.0;
	error_knee_l_ang_adjust = error_knee_l_ang * 1.0;
	error_ankle_l_ang_adjust = error_ankle_l_ang * 3.0;	
	error_hip_tx_adjust = error_hip_tx * 0.1;
	error_hip_ty_adjust = error_hip_ty * 30.0;
	error_hip_l_trq_adjust = error_hip_l_trq * 1.0; 
	error_knee_l_trq_adjust = error_knee_l_trq * 1.0;
	error_ankle_l_trq_adjust = error_ankle_l_trq * 1.0; 
	error_hip_l_pwr_adjust = error_hip_l_pwr * 1.0;
	error_knee_l_pwr_adjust = error_knee_l_pwr * 1.0;
	error_ankle_l_pwr_adjust = error_ankle_l_pwr * 1.0;
	error_grfz_l_adjust = error_grfz_l * 0.05;
	error_grfx_l_adjust = error_grfx_l * 0.5;
	error_grfz_r_adjust = error_grfz_r * 0.05;	
	error_grfx_r_adjust = error_grfx_r * 1.0; 
	error_ankle_l_vel_adjust = error_ankle_l_vel * 1.0;
	error_segme_adjust = error_segme * 1.0;
	error_pelvis_rot_adjust = error_pelvis_rot * 0.5;
	error_extpwr_adjust = error_extpwr * 1.0;
	error_sysme_adjust = error_sysme * 0.1;
	error_syske_adjust = error_syske * 0.1;
	error_syspe_adjust = error_syspe * 0.1;
	mus_power_adjust = mus_power * 0.0001;
	mus_exc_adjust = mus_exc * 1.0;
	error_Lgrf_on_adjust = error_Lgrf_on * 1000.0;
	
	


	COST = 	error_hip_r_ang_adjust + 
			error_knee_r_ang_adjust + 
			error_ankle_r_ang_adjust + 
			error_hip_l_ang_adjust + 
			error_knee_l_ang_adjust + 
			error_ankle_l_ang_adjust +	
			error_hip_tx_adjust + 
			error_hip_ty_adjust + 
			//error_hip_l_trq_adjust +
			//error_knee_l_trq_adjust + 
			//error_ankle_l_trq_adjust +
			//error_hip_l_pwr_adjust +
			//error_knee_l_pwr_adjust +
			//error_ankle_l_pwr_adjust +
			error_grfz_l_adjust +
			error_grfx_l_adjust +
			error_grfz_r_adjust +
			//error_grfx_r_adjust +
			//error_ankle_l_vel_adjust +
			error_pelvis_rot_adjust +
			error_extpwr_adjust +
			error_sysme_adjust+
			error_syske_adjust+
			error_syspe_adjust+
			mus_power_adjust+
			mus_exc_adjust+
			error_Lgrf_on_adjust;
			


	COST = COST / 20.0;
			
			mdata.err_hip_r_ang = error_hip_r_ang;
			mdata.err_knee_r_ang = error_knee_r_ang;
			mdata.err_ankle_r_ang = error_ankle_r_ang;
			mdata.err_hip_l_ang = error_hip_l_ang;
			mdata.err_knee_l_ang = error_knee_l_ang;
			mdata.err_ankle_l_ang = error_ankle_l_ang;
			mdata.err_hip_tx = error_hip_tx;
			mdata.err_hip_ty = error_hip_ty;
			mdata.err_grfz_l = error_grfz_l;
			mdata.err_hip_l_trq = error_hip_l_trq;
			mdata.err_knee_l_trq = error_knee_l_trq;
			mdata.err_ankle_l_trq = error_ankle_l_trq;
			mdata.err_hip_l_pwr = error_hip_l_pwr;
			mdata.err_knee_l_pwr = error_knee_l_pwr;
			mdata.err_ankle_l_pwr = error_ankle_l_pwr;
			mdata.err_grfx_l = error_grfx_l;
			mdata.err_ankle_l_vel = error_ankle_l_vel;
			mdata.err_grfz_r = error_grfz_r;
			mdata.err_segme = error_segme;
			mdata.err_grfx_r = error_grfx_r;
			mdata.err_pelvis_rot = error_pelvis_rot;
			mdata.err_extpwr = error_extpwr; // added 9-1-03
			mdata.err_sysme = error_sysme; // added 9-15-03
			mdata.err_syske = error_syske; // added 9-15-03
			mdata.err_syspe = error_syspe; // added 9-15-03
			mdata.total_muspower = mus_power; //added 8-17-04
			mdata.err_Lgrf_on = error_Lgrf_on; //added 10-21-04
			mdata.total_musexc = mus_exc; //added 8-06-07

			mdata.err_adjusted_hip_r_ang = error_hip_r_ang_adjust;
			mdata.err_adjusted_knee_r_ang = error_knee_r_ang_adjust;
			mdata.err_adjusted_ankle_r_ang = error_ankle_r_ang_adjust;
			mdata.err_adjusted_hip_l_ang = error_hip_l_ang_adjust;
			mdata.err_adjusted_knee_l_ang = error_knee_l_ang_adjust;
			mdata.err_adjusted_ankle_l_ang = error_ankle_l_ang_adjust;
			mdata.err_adjusted_hip_tx = error_hip_tx_adjust;
			mdata.err_adjusted_hip_ty = error_hip_ty_adjust;
			mdata.err_adjusted_grfz_l = error_grfz_l_adjust;
			mdata.err_adjusted_hip_l_trq = error_hip_l_trq_adjust;
			mdata.err_adjusted_knee_l_trq = error_knee_l_trq_adjust;
			mdata.err_adjusted_ankle_l_trq = error_ankle_l_trq_adjust;
			mdata.err_adjusted_hip_l_pwr = error_hip_l_pwr_adjust;
			mdata.err_adjusted_knee_l_pwr = error_knee_l_pwr_adjust;
			mdata.err_adjusted_ankle_l_pwr = error_ankle_l_pwr_adjust;
			mdata.err_adjusted_grfx_l = error_grfx_l_adjust;
			mdata.err_adjusted_ankle_l_vel = error_ankle_l_vel_adjust;
			mdata.err_adjusted_grfz_r = error_grfz_r_adjust;
			mdata.err_adjusted_segme = error_segme_adjust;
			mdata.err_adjusted_grfx_r = error_grfx_r_adjust;
			mdata.err_adjusted_pelvis_rot = error_pelvis_rot_adjust;
			mdata.err_adjusted_extpwr = error_extpwr_adjust; //added 9-1-03
			mdata.err_adjusted_sysme = error_sysme_adjust; //added 9-15-03
			mdata.err_adjusted_syske = error_syske_adjust; //added 9-15-03
			mdata.err_adjusted_syspe = error_syspe_adjust; //added 9-15-03
			mdata.total_adjusted_muspower = mus_power_adjust; //added 8-17-04
			mdata.err_Lgrf_on_adjusted = error_Lgrf_on_adjust; //added 10-21-04
			mdata.total_adjusted_musexc = mus_exc_adjust; //added 8-06-07

	return COST;

}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
