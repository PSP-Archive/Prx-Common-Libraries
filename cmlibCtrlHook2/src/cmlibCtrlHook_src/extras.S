	.set noreorder

.global sceCtrlCommonFuncPatched
.ent	sceCtrlCommonFuncPatched
sceCtrlCommonFuncPatched:

	# backup register
	sw $s0, 0($sp)
	sw $s1, 4($sp)

	# backup argument
	move $s0, $a0

	# backup return_address($ra)
	move $s1, $ra

	# push
	addiu $sp, $sp, -48

	# The part invalid with a patch
	sw $s1, 4($sp)
	lui $t0, 0x8000

	# overwritten return_address($ra)
	lui $ra, %hi(sceCtrlCommonFuncLauncher)
	addiu $ra, $ra, %lo(sceCtrlCommonFuncLauncher)

	# jump sceCtrlCommonFunc
	lui $s1, %hi(ctrl_jump_addr)
	addiu $s1, $s1, %lo(ctrl_jump_addr)
	lw $s1, 0($s1)
	jr $s1
	nop

.end sceCtrlCommonFuncPatched

.global sceCtrlCommonFuncOldPatched
.ent	sceCtrlCommonFuncOldPatched
sceCtrlCommonFuncOldPatched:

	# backup register
	sw $s0, 0($sp)
	sw $s1, 4($sp)

	# backup argument
	move $s0, $a0

	# backup return_address($ra)
	move $s1, $ra

	# push
	addiu $sp, $sp, -32

	# move argument
	move $a2, $a3

	# The part invalid with a patch
	sw $s1, 4($sp)
	lui $a3, 0x8000

	# overwritten return_address($ra)
	lui $ra, %hi(sceCtrlCommonFuncOldLauncher)
	addiu $ra, $ra, %lo(sceCtrlCommonFuncOldLauncher)

	# jump sceCtrlCommonFunc
	lui $s1, %hi(ctrl_jump_addr)
	addiu $s1, $s1, %lo(ctrl_jump_addr)
	lw $s1, 0($s1)
	jr $s1
	nop

.end sceCtrlCommonFuncOldPatched

.global sceCtrlCommonFuncLauncher
.ent	sceCtrlCommonFuncLauncher
sceCtrlCommonFuncLauncher:

	# restore argument
	move $a0, $s0

	# set return_value($v0)
	move $a1, $v0

	# call
	jal sceCtrlCommonFuncControl
	nop

	# restore return_address($ra)
	move $ra, $s1

	# restore register
	lw $s0, 0($sp)
	lw $s1, 4($sp)

	# pop
	addiu $sp, $sp, 48

	# return
	jr $ra
	nop

.end sceCtrlCommonFuncLauncher

.global sceCtrlCommonFuncOldLauncher
.ent	sceCtrlCommonFuncOldLauncher
sceCtrlCommonFuncOldLauncher:

	# restore argument
	move $a0, $s0

	# set return_value($v0)
	move $a1, $v0

	# call
	jal sceCtrlCommonFuncControl
	nop

	# restore return_address($ra)
	move $ra, $s1

	# restore register
	lw $s0, 0($sp)
	lw $s1, 4($sp)

	# pop
	addiu $sp, $sp, 32

	# return
	jr $ra
	nop

.end sceCtrlCommonFuncOldLauncher

.global sceCtrlCommonFunc
.ent	sceCtrlCommonFunc
sceCtrlCommonFunc:

	# original_function_work
	addiu $sp, $sp, -48
	addiu $v1, $a1, -1
	sw $s1, 4($sp)
	lui $t0, 0x8000

	# jump sceCtrlCommonFunc
	lui $s1, %hi(ctrl_jump_addr)
	addiu $s1, $s1, %lo(ctrl_jump_addr)
	lw $s1, 0($s1)
	jr $s1
	nop

.end sceCtrlCommonFunc

.global sceCtrlCommonOldFunc
.ent	sceCtrlCommonOldFunc
sceCtrlCommonOldFunc:

	# move argument
	move $a2, $a3

	# original_function_work
	addiu $sp, $sp, -32
	addiu $v1, $a1, -1
	sw $s1, 4($sp)
	lui $a3, 0x8000

	# jump sceCtrlCommonFunc
	lui $s1, %hi(ctrl_jump_addr)
	addiu $s1, $s1, %lo(ctrl_jump_addr)
	lw $s1, 0($s1)
	jr $s1
	nop

.end sceCtrlCommonOldFunc

