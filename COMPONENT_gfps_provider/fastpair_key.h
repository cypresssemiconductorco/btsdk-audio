/*
 * Copyright 2020, Cypress Semiconductor Corporation or a subsidiary of
 * Cypress Semiconductor Corporation. All Rights Reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software"), is owned by Cypress Semiconductor Corporation
 * or one of its subsidiaries ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products. Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */
/** @file
*
* Google Fast Pair header file
*
* This file provides definitions and function prototypes for account keys
*
*/
#pragma once

/** SHA define */
#define HW_SECENG_POLLING       1
#define HW_SECENG_INTERRUPT     0
#define HW_SECENG_FREE          0
typedef enum
{
    HW_SHA2_FREE = HW_SECENG_FREE,    //0
    HW_SHA2_BUSY,                     //1
    HW_SHA2_PARAM_ERROR,              //2
    HW_SHA2_PARAM_CORRECT,            //3
    HW_SHA2_CFG_DONE,                 //4
    HW_SHA2_COMPLETE,                 //5
}tHW_SHA2_STATUS;

typedef enum
{
    HW_SHA256,                        //0
    HW_SHA224,                        //1
    HW_SHA384,                        //2
    HW_SHA512,                        //3
    HW_SHA512_256,                    //4
    HW_SHA512_224,                    //5
}tHW_SHA2_MODE;

typedef struct _tHW_SHA2 tHW_SHA2;
typedef void (*tHW_SHA2_CALLBACK)(tHW_SHA2 *pst_hw_sha2);

typedef struct _tHW_SHA2
{
    uint8_t  polling_flag;              /* Polling (HW_SECENG_POLLING) or Interrupt (HW_SECENG_INTERRUPT)                                  */
    uint8_t  hmac_en ;                  /* HMAC-SHA2(1) or SHA2 only(0)                                                                    */
    uint8_t  sha2_mode;                 /* HW_SHA256     (0)                                                                               */
                                      /* HW_SHA224     (1)                                                                               */
                                      /* HW_SHA384     (2)                                                                               */
                                      /* HW_SHA512     (3)                                                                               */
                                      /* HW_SHA512_256 (4)                                                                               */
                                      /* HW_SHA512_224 (5)                                                                               */
    uint16_t  msg_len;                  /* The length of message to be hashed in bytes: 1-65535.                                           */
    uint16_t  key_len;                  /* The length of keys in byte: 1 - 1023                                                            */
    uint8_t *key_ptr;                  /* The pointer points to keys.  MUST be aligned to 4-bytes.                                        */
    uint32_t *in_ptr;                   /* The pointer points to input message to be hashed. MUST be aligned to 4-bytes.                   */
    uint8_t  *out_ptr;                  /* The pointer points to output hash values.                                                       */
    tHW_SHA2_CALLBACK callback;       /* Call back function for HW SHA2 if using interrupt.                                              */
    tHW_SHA2  *hw_sha2_next;          /* The pointer points to the next data structure in the waiting line.                              */
}tHW_SHA2;


/** SHA define */
#define uECC_BYTES   32

/** External functions define */
extern uint8_t hw_sha2_engine(tHW_SHA2 *hw_sha2);

extern int uECC_shared_secret(const uint8_t public_key[uECC_BYTES*2],
                       const uint8_t private_key[uECC_BYTES],
                       uint8_t secret[uECC_BYTES]);

extern void aes_ecb_128_decrypt(uint8_t *p_dout, uint8_t *p_din, uint8_t *p_key);
extern void aes_ecb_128_encrypt(uint8_t *p_dout, uint8_t *p_din, uint8_t *p_key);