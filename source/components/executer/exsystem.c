
/******************************************************************************
 * 
 * Module Name: iesystem - Interface to OS services
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, Intel Corp.  All rights
 * reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.  
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee 
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.  
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
 * Intel shall be used in advertising or otherwise to promote the sale, use or
 * other dealings in products derived from or relating to the Covered Code
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED
 * HERE.  ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT,  ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES.  INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS.  INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE. 
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.  THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government.  In the
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/

#define __IESYSTEM_C__

#include <acpi.h>
#include <interpreter.h>
#include <namespace.h>


#define _COMPONENT          INTERPRETER
        MODULE_NAME         ("iesystem");



/******************************************************************************
 * 
 * FUNCTION:    OsThreadId
 *
 * PARAMETERS:  None
 *
 * RETURN:      Current Thread ID (for this implementation a 1 is returned)
 *
 * DESCRIPTION: An invocation is identified by its Thread ID.  In a single
 *              threaded OS the Thread ID is undefined so a 1 will be
 *              returned.
 *
 ******************************************************************************/

UINT16 
OsThreadId (void)
{
    return (1);
}


/******************************************************************************
 * 
 * FUNCTION:    OsDoSuspend
 *
 * PARAMETERS:  HowLong             - The amount of time to suspend
 *
 * RETURN:      None
 *
 * DESCRIPTION: Suspend running thread for specified amount of time.
 *
 ******************************************************************************/

void
OsDoSuspend (
    UINT32                  HowLong)
{
    OsdSleep ((UINT16) (HowLong / (UINT32) 1000), (UINT16) (HowLong % (UINT32) 1000));
}


/******************************************************************************
 * 
 * FUNCTION:    OsAcquireOpRqst
 *
 * PARAMETERS:  *TimeDesc           - The 'time to delay' object descriptor
 *              *ObjDesc            - The object descriptor for this op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *              within the AML.  This function will cause a lock to be generated
 *              for the Mutex pointed to by ObjDesc.
 *
 *             TBD: Timeout is being ignored for now since this is single threaded.
 *
 ******************************************************************************/

ACPI_STATUS
OsAcquireOpRqst (
    ACPI_OBJECT_INTERNAL    *TimeDesc, 
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{
    UINT16                  CurrentId;
    ACPI_STATUS             Status = AE_OK;



    FUNCTION_TRACE ("OsAcquireOpRqst");

    if (ObjDesc)
    {
        if (ObjDesc->Mutex.LockCount == 0)
        {
            ObjDesc->Mutex.ThreadId = OsThreadId ();
        }
    
        else if (ObjDesc->Mutex.ThreadId != (CurrentId = OsThreadId ()))
        {
            DEBUG_PRINT (ACPI_ERROR, ("Thread %02Xh attempted to acquire a resource owned "
                    "by thread %02Xh\n", CurrentId, ObjDesc->Mutex.ThreadId));
            Status = AE_SHARE;
        }

        if (AE_OK == Status)
        {
            ObjDesc->Mutex.LockCount++;
        }
    }

    return_ACPI_STATUS (Status);
}


/******************************************************************************
 * 
 * FUNCTION:    OsReleaseOpRqst
 *
 * PARAMETERS:  *ObjDesc            - The object descriptor for this op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *              within the AML.  This operation is a request to release a previously
 *              acquired Mutex.  If the Mutex variable is set then it will be
 *              decremented.
 *
 ******************************************************************************/

ACPI_STATUS
OsReleaseOpRqst (
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{
    UINT16                  CurrentId;
    ACPI_STATUS             Status = AE_OK;


    FUNCTION_TRACE ("OsReleaseOpRqst");

    
    if (ObjDesc)
    {
        if (ObjDesc->Mutex.LockCount == 0)
        {
            DEBUG_PRINT (ACPI_ERROR, ("Attempting to Release a Mutex that is not locked\n"));
            Status = AE_ERROR;
        }
    
        else if (ObjDesc->Mutex.ThreadId != (CurrentId = OsThreadId ()))
        {
            DEBUG_PRINT (ACPI_ERROR, ("Thread %02Xh attempted to release a Mutex owned "
                        "by thread %02Xh\n", CurrentId, ObjDesc->Mutex.ThreadId));
            Status = AE_SHARE;
        }
    
        if (AE_OK == Status)
        {
            ObjDesc->Mutex.LockCount--;
        }
    }

    return_ACPI_STATUS (Status);
}


/******************************************************************************
 * 
 * FUNCTION:    OsSignalOpRqst
 *
 * PARAMETERS:  *ObjDesc            - The object descriptor for this op
 *
 * RETURN:      AE_OK
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *              within the AML.  This will signal when an event has been posted.
 *              if this occures prior to a wait then the wait will succeed.
 *              if a wait occures without a signal then the wait will fail
 *              because the signal will never occur.
 *
 ******************************************************************************/

ACPI_STATUS
OsSignalOpRqst (
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{

    if (ObjDesc)
    {
        ObjDesc->Event.SignalCount++;
    }

    return (AE_OK);
}


/******************************************************************************
 * 
 * FUNCTION:    OsWaitOpRqst
 *
 * PARAMETERS:  *TimeDesc           - The 'time to delay' object descriptor
 *              *ObjDesc            - The object descriptor for this op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *              within the AML.  This operation is a request to wait for an event.
 *              In a single thread OS,  if the signal for this event has
 *              already occured then dec the signal count and return success.
 *              If the signal has not already occured then it never will
 *              because the wait would have to give the processor over to a
 *              new process and that can't happen in a single threaded OS.
 *
 *              TBD: Timeout is being ignored for the current implementation.
 *
 ******************************************************************************/

ACPI_STATUS
OsWaitOpRqst (
    ACPI_OBJECT_INTERNAL    *TimeDesc, 
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{
    ACPI_STATUS             Status = AE_OK;


    if (ObjDesc)
    {
        if (0 == ObjDesc->Event.SignalCount)
        {
            /* Error for single threaded OS */
        
            DEBUG_PRINT (ACPI_ERROR, ("Waiting for a signal that has not occured.  In a single threaded"
                    "\nOperating System the signal would never be received.\n"));
            Status = AE_ERROR;
        }
    
        else
        {
            ObjDesc->Event.SignalCount--;
        }
    }
  
    return (Status);
}


/******************************************************************************
 * 
 * FUNCTION:    OsResetOpRqst
 *
 * PARAMETERS:  *ObjDesc            - The object descriptor for this op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Provides an access point to perform synchronization operations
 *              within the AML.  Current implementation is for single thread
 *              OS only.  This will reset the total signal count for this
 *              event to 0.
 *
 ******************************************************************************/

ACPI_STATUS
OsResetOpRqst (
    ACPI_OBJECT_INTERNAL    *ObjDesc)
{
    ACPI_STATUS             Status = AE_OK;


    if (ObjDesc)
    {
        ObjDesc->Event.SignalCount = 0;
    }

    return (Status);
}


/***************************************************************************
 * 
 * FUNCTION:    OsGetGlobalLock
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Attempts to gain ownership of the Global Lock.  
 *
 *              TBD: Since this
 *              is a single threaded implementation if the Global Lock
 *              ownership is not successful then the test will fail.
 *
 **************************************************************************/

ACPI_STATUS
OsGetGlobalLock(void)
{
    UINT32              GlobalLockReg;
    ACPI_STATUS         Status = AE_OK;


    if (Gbl_FACS)
    {
        /* Only if the FACS is valid */

        GlobalLockReg = Gbl_FACS->GlobalLock;

        if (GlobalLockReg & GL_OWNED)
        {
            DEBUG_PRINT (ACPI_ERROR, ("The Global Lock is owned by another process\n"\
                    "This is a single threaded implementation. There is no way some\n"\
                    "other process can own the Global Lock!\n"));
            Status = AE_SHARE;
        }
    
        else
        {
            /* Its not owned so take ownership and return AE_OK */
        
            Gbl_FACS->GlobalLock |= GL_OWNED;
            Status = AE_OK;
        }
    }

    return (Status);
}


/***************************************************************************
 * 
 * FUNCTION:    OsReleaseGlobalLock
 *
 * DESCRIPTION: Releases ownership of the Global Lock.
 *
 **************************************************************************/

void
OsReleaseGlobalLock (void)
{
    
    if (Gbl_FACS)
    {
        Gbl_FACS->GlobalLock &= 0xFFFFFFFF ^ GL_OWNED;
    }
}
