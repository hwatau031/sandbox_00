using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Camera : MonoBehaviour
{
    [SerializeField] Transform playerTr; // プレイヤーのTransform
    [SerializeField] Vector3 cameraOffset = new Vector3(0, 1, -2); // プレイヤーからの相対的なカメラのオフセット (Y:1, Z:-1)
    [SerializeField] float lookAtYOffset = 0.5f; // カメラがプレイヤーを見るY軸のオフセット
    [SerializeField] Vector3 camaraMaxPos = new Vector3(5, 5, 10); // カメラの右上限界座標
    [SerializeField] Vector3 camaraMinPos = new Vector3(-5, -5, -10); // カメラの左下限界座標
    [SerializeField] float smoothSpeed = 3.0f; // カメラの追従速度

    // 全てのUpdateが終わった後に呼ばれるUpdate
    void LateUpdate()
    {
        // プレイヤーの位置にオフセットを適用した目標位置
        Vector3 desiredPosition = playerTr.position + cameraOffset;

        // 滑らかに目標位置に追従
        Vector3 smoothedPosition = Vector3.Lerp(transform.position, desiredPosition, smoothSpeed * Time.deltaTime);

        // カメラの位置を制限
        smoothedPosition.x = Mathf.Clamp(smoothedPosition.x, camaraMinPos.x, camaraMaxPos.x);
        smoothedPosition.y = Mathf.Clamp(smoothedPosition.y, camaraMinPos.y, camaraMaxPos.y);
        smoothedPosition.z = Mathf.Clamp(smoothedPosition.z, camaraMinPos.z, camaraMaxPos.z);
        transform.position = smoothedPosition;

        // カメラが向くターゲットのY座標にオフセットを加える
        Vector3 lookAtTarget = playerTr.position;
        lookAtTarget.y += lookAtYOffset; // Y軸に0.5加算

        // プレイヤーにカメラを向ける
        transform.LookAt(lookAtTarget);
    }
}
