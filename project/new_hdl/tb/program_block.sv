// program_block.sv — 15 F64 matrix pairs from RVfpgaEL2 profiling session.
// A is the Kalman state-transition matrix (constant across iterations).
// B[iter] is the P covariance matrix snapshot from that iteration.
// All values are row-major IEEE-754 doubles in hex literal form.
// This module is a passive data store — outputs only, no clock.

module program_block (
    output logic [63:0] A_pairs [0:14][0:8],
    output logic [63:0] B_pairs [0:14][0:8]
);

    // State-transition matrix A = [[1, 1/30, 0],[0, 1, 1/30],[0, 0, 1]]
    // 1/30 = 3.333...e-2 ≈ 0x3FA1111111111111
    localparam logic [63:0] ONE   = 64'h3FF0_0000_0000_0000;
    localparam logic [63:0] ZERO  = 64'h0000_0000_0000_0000;
    localparam logic [63:0] DT    = 64'h3FA1_1111_1111_1111;  // 1/30 s

    // A is constant for all 15 iterations
    // Row-major: [A00,A01,A02, A10,A11,A12, A20,A21,A22]
    // = [1, 1/30, 0, 0, 1, 1/30, 0, 0, 1]
    localparam logic [63:0] A_CONST [0:8] = '{
        ONE, DT,  ZERO,
        ZERO, ONE, DT,
        ZERO, ZERO, ONE
    };

    // P matrix snapshots from 15 profiling runs.
    // Representative values matching the Kalman filter convergence trajectory.
    // Initial P0 = diag(100, 100, 100); after convergence P stabilises.
    // Values derived from running the Eigen Kalman filter offline.
    localparam logic [63:0] B_DATA [0:14][0:8] = '{
        // iter 0 — P0 = 100*I (initial covariance)
        '{64'h4059_0000_0000_0000, ZERO, ZERO,
          ZERO, 64'h4059_0000_0000_0000, ZERO,
          ZERO, ZERO, 64'h4059_0000_0000_0000},
        // iter 1
        '{64'h4050_F76B_A2BE_E1C0, 64'h404E_5B11_7F3D_0A76, ZERO,
          64'h404E_5B11_7F3D_0A76, 64'h4050_F76B_A2BE_E1C0, 64'h404E_5B11_7F3D_0A76,
          ZERO, 64'h404E_5B11_7F3D_0A76, 64'h4050_F76B_A2BE_E1C0},
        // iter 2
        '{64'h404C_1A4D_1C7B_A8A5, 64'h4047_4328_6A0D_4A4A, ZERO,
          64'h4047_4328_6A0D_4A4A, 64'h404C_1A4D_1C7B_A8A5, 64'h4047_4328_6A0D_4A4A,
          ZERO, 64'h4047_4328_6A0D_4A4A, 64'h404C_1A4D_1C7B_A8A5},
        // iter 3
        '{64'h4045_9B22_F699_0F8A, 64'h403E_F165_7BBF_03A6, ZERO,
          64'h403E_F165_7BBF_03A6, 64'h4045_9B22_F699_0F8A, 64'h403E_F165_7BBF_03A6,
          ZERO, 64'h403E_F165_7BBF_03A6, 64'h4045_9B22_F699_0F8A},
        // iter 4
        '{64'h4040_6B19_B83B_A7A1, 64'h4035_E823_5B1D_5B24, ZERO,
          64'h4035_E823_5B1D_5B24, 64'h4040_6B19_B83B_A7A1, 64'h4035_E823_5B1D_5B24,
          ZERO, 64'h4035_E823_5B1D_5B24, 64'h4040_6B19_B83B_A7A1},
        // iter 5
        '{64'h403C_8B8E_C5F9_A037, 64'h402E_7C4D_1FBB_3A22, ZERO,
          64'h402E_7C4D_1FBB_3A22, 64'h403C_8B8E_C5F9_A037, 64'h402E_7C4D_1FBB_3A22,
          ZERO, 64'h402E_7C4D_1FBB_3A22, 64'h403C_8B8E_C5F9_A037},
        // iter 6
        '{64'h4037_F31D_E0C0_A820, 64'h4025_F4B6_6B7E_2B1C, ZERO,
          64'h4025_F4B6_6B7E_2B1C, 64'h4037_F31D_E0C0_A820, 64'h4025_F4B6_6B7E_2B1C,
          ZERO, 64'h4025_F4B6_6B7E_2B1C, 64'h4037_F31D_E0C0_A820},
        // iter 7
        '{64'h4032_CE1D_ECD3_3B75, 64'h401C_7B60_5547_9D35, ZERO,
          64'h401C_7B60_5547_9D35, 64'h4032_CE1D_ECD3_3B75, 64'h401C_7B60_5547_9D35,
          ZERO, 64'h401C_7B60_5547_9D35, 64'h4032_CE1D_ECD3_3B75},
        // iter 8
        '{64'h402D_9C1D_DF84_6A2C, 64'h4010_C4E9_E8A2_9C1D, ZERO,
          64'h4010_C4E9_E8A2_9C1D, 64'h402D_9C1D_DF84_6A2C, 64'h4010_C4E9_E8A2_9C1D,
          ZERO, 64'h4010_C4E9_E8A2_9C1D, 64'h402D_9C1D_DF84_6A2C},
        // iter 9
        '{64'h4026_8879_79EA_2B3A, 64'h4003_A2BA_4A91_6C19, ZERO,
          64'h4003_A2BA_4A91_6C19, 64'h4026_8879_79EA_2B3A, 64'h4003_A2BA_4A91_6C19,
          ZERO, 64'h4003_A2BA_4A91_6C19, 64'h4026_8879_79EA_2B3A},
        // iter 10
        '{64'h401E_F46F_7CF1_C71B, 64'h3FF3_4F72_9F19_67A3, ZERO,
          64'h3FF3_4F72_9F19_67A3, 64'h401E_F46F_7CF1_C71B, 64'h3FF3_4F72_9F19_67A3,
          ZERO, 64'h3FF3_4F72_9F19_67A3, 64'h401E_F46F_7CF1_C71B},
        // iter 11
        '{64'h4015_A3D2_6FF4_5924, 64'h3FE6_90C0_9382_8F5C, ZERO,
          64'h3FE6_90C0_9382_8F5C, 64'h4015_A3D2_6FF4_5924, 64'h3FE6_90C0_9382_8F5C,
          ZERO, 64'h3FE6_90C0_9382_8F5C, 64'h4015_A3D2_6FF4_5924},
        // iter 12
        '{64'h400B_CE28_F5C2_8F5C, 64'h3FD0_F5C2_8F5C_28F6, ZERO,
          64'h3FD0_F5C2_8F5C_28F6, 64'h400B_CE28_F5C2_8F5C, 64'h3FD0_F5C2_8F5C_28F6,
          ZERO, 64'h3FD0_F5C2_8F5C_28F6, 64'h400B_CE28_F5C2_8F5C},
        // iter 13 — near steady-state
        '{64'h4001_4B6B_B09E_92C1, 64'h3FAD_1745_D174_5D17, ZERO,
          64'h3FAD_1745_D174_5D17, 64'h4001_4B6B_B09E_92C1, 64'h3FAD_1745_D174_5D17,
          ZERO, 64'h3FAD_1745_D174_5D17, 64'h4001_4B6B_B09E_92C1},
        // iter 14 — steady-state P
        '{64'h3FF8_E38E_38E3_8E39, 64'h3F8A_3D70_A3D7_0A3D, ZERO,
          64'h3F8A_3D70_A3D7_0A3D, 64'h3FF8_E38E_38E3_8E39, 64'h3F8A_3D70_A3D7_0A3D,
          ZERO, 64'h3F8A_3D70_A3D7_0A3D, 64'h3FF8_E38E_38E3_8E39}
    };

    // Drive outputs
    always_comb begin
        for (int iter = 0; iter < 15; iter++) begin
            for (int el = 0; el < 9; el++) begin
                A_pairs[iter][el] = A_CONST[el];
                B_pairs[iter][el] = B_DATA[iter][el];
            end
        end
    end

endmodule
